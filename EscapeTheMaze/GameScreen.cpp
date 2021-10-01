#include "libraries.h"
#include "Player.h"
#include "GameScreen.h"

void GameScreen::render(sf::RenderWindow& target, std::string& state)
{
	if (state == "Game") {
		target.setView(mainView);
		
		target.draw(*background);
		player->render(target);
		target.setView(target.getDefaultView());
		target.draw(congratsText);
		for (int i = 0; i < instructions.size(); ++i) {
			target.draw(instructions[i]);
		}
	}
}

void GameScreen::update(sf::RenderWindow& target, std::string& state)
{
	if (state == "Game" && !gameFrozen) {
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			state = "Starting";
			std::cout << "B pressed";
		}
		if (!isSolved && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			solveMaze();
		player->update(walls);
		mainView.setCenter(player->getPlayerCenter());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
			mainView.zoom(zoomSpeed + zoom);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
			mainView.zoom(zoom - zoomSpeed);
		}
		if (player->body.getGlobalBounds().intersects(lastCell.getGlobalBounds())) {
			congratsText.setScale(1.f, 1.f);
			congratsText.setPosition(sf::Vector2f(target.getSize().x / 2 - congratsText.getGlobalBounds().width / 2, target.getSize().y / 2));
			gameFrozen = true;
		}
	}
	if (state == "Game" && gameFrozen) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			state = "Starting";
	}
}

GameScreen::GameScreen(int width,int height)
{
	if (!font.loadFromFile("Fonts/sewer.ttf")) {
		std::cout << "Font not loaded\n";
		//return;
	}
	gameFrozen = false;

	congratsText.setFont(font);
	congratsText.setCharacterSize(40);
	congratsText.setFillColor(sf::Color::Green);
	congratsText.setString("Congratulations for finishing. Press p to play again");
	congratsText.setScale(0.f, 0.f);

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Magenta);
	text.setString("Press B to go back to the main screen");
	text.setPosition(10.f, text.getLocalBounds().height * 0);
	instructions.push_back(text);
	text.setString("Press PLUS and MINUS to zoom in or our");
	text.setPosition(10.f, text.getLocalBounds().height * 1);
	instructions.push_back(text);
	text.setString("Press SPACE to solve the maze");
	text.setPosition(10.f, text.getLocalBounds().height * 2);
	instructions.push_back(text);
	text.setString("Use W A S D to move");
	text.setPosition(10.f, text.getLocalBounds().height * 3);
	instructions.push_back(text);


	zoomSpeed = 0.01f;
	zoom = 1.f;
	mainView.setSize(1920, 1080);
	mainView.zoom(zoom);
	walls.clear();
	passageSize = 75;
	wallSize = 15;

	int i, j;
	int n = height * 2;
	int m = width * 2;
	maze_width = width;
	maze_height = height;
	maze = new int* [height];
	for (i = 0; i < height; ++i)
		maze[i] = new int[width];
	for (i = 0; i < height; ++i) 
		for (j = 0; j < width; ++j) 
			maze[i][j] = 1;
	createMaze();
	bgTexture.create(10000, 10000);
	drawMaze();
	bgTexture.display();
	background = new sf::Sprite(bgTexture.getTexture());
	player = new Player();
	isSolved = 0;
	
}

GameScreen::~GameScreen()
{
	delete player;
	delete background;
	delete maze;
}


void GameScreen::drawMaze()
{
	bgTexture.clear();
	
	int i, j, n = maze_height * 2, m = maze_width * 2;
	sf::RectangleShape r;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j) {
			
			if (i % 2) {
				r.setSize(sf::Vector2f(passageSize * 1.0f, wallSize * 1.0f));
				r.setPosition(sf::Vector2f(j / 2 * wallSize + (j / 2) * passageSize, i / 2 * wallSize + (i / 2 + 1) * passageSize));
				if (j % 2) {
					r.setSize(sf::Vector2f(wallSize * 1.0f, wallSize * 1.0f));
					r.setPosition(sf::Vector2f(j / 2 * wallSize + (j / 2 + 1) * passageSize, i / 2 * wallSize + (i / 2 + 1) * passageSize));
				}
			}
			else if (j % 2) {
				r.setSize(sf::Vector2f(wallSize * 1.0f, passageSize * 1.0f));
				r.setPosition(sf::Vector2f(j / 2 * wallSize + (j / 2 + 1) * passageSize, i / 2 * wallSize + (i / 2) * passageSize));
			}
			else {
				r.setSize(sf::Vector2f(passageSize * 1.0f, passageSize * 1.0f));
				r.setPosition(sf::Vector2f((passageSize + wallSize) * (j / 2), (passageSize + wallSize) * (i / 2)));
			}
			switch (maze[i][j])
			{
			case 0:
				r.setFillColor(sf::Color::White);
				lastCell = r;
				break;
			case 1:
				r.setFillColor(sf::Color::Black);
				walls.push_back(r);
				break;
			case 2:
				r.setFillColor(sf::Color::Cyan);
				lastCell = r;
				break;
			default:
				break;
			}
			bgTexture.draw(r);
		}
	}
}

void GameScreen::solveMaze()
{
	isSolved = 1;
	const int infinite = 1000000000;
	int n = maze_height * 2;
	int m = maze_width * 2;
	std::pair <int, int> current;
	std::pair <int, int> next;
	std::queue <std::pair<int, int>>q;
	std::vector<std::vector<int>> dij(n, std::vector<int>(m, infinite));
	current.first = current.second = 0;
	q.push(current);
	const int dy[] = { 0,1,0,-1 };
	const int dx[] = { -1,0,1,0 };
	int i, j;
	dij[0][0] = 0;
	while (!q.empty()) {
		current = q.front();
		
		q.pop();
		for (i = 0; i < 4; ++i) {
			next.first = current.first + dx[i];
			next.second = current.second + dy[i];
			if (next.first >= 0 && next.second >= 0 && next.first < n && next.second < m && maze[next.first][next.second] == 0 && 1 + dij[current.first][current.second] < dij[next.first][next.second]) {
				q.push(next);
				dij[next.first][next.second] = dij[current.first][current.second] + 1;
			}
		}
	}
	current.first = n - 2;
	current.second = m - 2;
	maze[0][0] = 2;
	bool ok = true;
	
	while (!(current.first==0 && current.second==0)) {
		maze[current.first][current.second] = 2;
		if(current.first == 0 && current.second == 0)
		{
			ok = false;
		}
		for (i = 0; i < 4; ++i) {
			next.first = current.first + dx[i];
			next.second = current.second + dy[i];
			if (next.first >= 0 && next.second >= 0 && next.first < n && next.second < m && dij[next.first][next.second] + 1 == dij[current.first][current.second]) {
				current = next;
				i = 4;
			}
		}
	}
	drawMaze();
}

void GameScreen::createMaze()
{
	if (maze_height != 0 && maze_width != 0) {
		std::srand(std::time(NULL));
		const int dy[] = { 0,1,0,-1 };
		const int dx[] = { -1,0,1,0 };
		int i, j;
		int n = maze_height * 2;
		int m = maze_width * 2;

		maze = new int* [n];
		for (i = 0; i < n; ++i)
			maze[i] = new int[m];
		for (i = 0; i < n / 2; ++i)
			for (j = 0; j < m / 2; ++j) {
				maze[2 * i][2 * j] = 0;
				maze[2 * i + 1][2 * j] = 1;
				maze[2 * i + 1][2 * j + 1] = 1;
				maze[2 * i][2 * j + 1] = 1;
			}
		int totalCells = maze_width * maze_height;
		int currentCells = 0;
		int neighbours, randomNeighbour;

		std::vector<std::vector<int>> viz(n, std::vector<int>(m, 0));
		std::stack <std::pair<int, int>> st;
		std::pair<int, int> p;
		std::pair<int, int>next;
		std::vector<std::pair<int, int>>vecini;
		p.first = 0;
		p.second = 0;
		st.push(p);
		while (currentCells < totalCells) {
			neighbours = 0;
			p = st.top();
			for (i = 0; i < 4; ++i) {
				next.first = p.first + dx[i];
				next.second = p.second + dy[i];
				if (next.first >= 0 && next.second >= 0 && next.first < maze_height && next.second < maze_width && viz[next.first][next.second] == 0) {
					neighbours++;
					vecini.push_back(next);
				}
			}
			if (neighbours == 0) {
				st.pop();
			}
			else {
				randomNeighbour = std::rand() % neighbours;
				next = vecini[randomNeighbour];
				vecini.clear();
				st.push(next);
				maze[((p.first * 2) + (next.first * 2)) / 2][((p.second * 2) + (next.second * 2)) / 2] = 0;
				viz[next.first][next.second] = 1;
				currentCells++;
			}
		}
	}
	
	
}


