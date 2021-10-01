#pragma once
#include "libraries.h"
#include "Player.h"

#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <string>

class GameScreen
{
	sf::Font font;

	sf::Text congratsText;
	std::vector<sf::Text>instructions;

	sf::View mainView;
	Player* player;
	int** maze;
	int passageSize;
	int wallSize;
	void createMaze();
	sf::RenderTexture bgTexture;
	sf::Sprite* background;
	void drawMaze();
	std::vector<sf::RectangleShape>walls;
	void solveMaze();
	bool isSolved;
	bool gameFrozen;
	float zoomSpeed;
	float zoom;
	sf::RectangleShape lastCell;
public:
	int maze_width;
	int maze_height;
	void render(sf::RenderWindow&,std::string&);
	void update(sf::RenderWindow&,std::string&);

	GameScreen(int, int);
	~GameScreen();
};

