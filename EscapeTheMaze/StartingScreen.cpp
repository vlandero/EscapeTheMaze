#include "libraries.h"
#include "StartingScreen.h"

void StartingScreen::render(sf::RenderWindow &w, std::string& state)
{
	if (state == "Starting") {
		w.draw(this->chooseText);
		w.draw(this->hardText);
		w.draw(this->easyText);
		w.draw(this->mediumText);
	}
}

void StartingScreen::update(sf::RenderWindow &w, GameScreen*& game, std::string& state)
{
	
	if (state == "Starting") {
		mouseProv = sf::Mouse::getPosition(w);
		this->mousePosition = w.mapPixelToCoords(this->mouseProv);

		if (state == "Starting") {
			if (this->easyText.getGlobalBounds().contains(this->mousePosition))
			{
				easyText.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					
					delete game;
					game = new GameScreen(20, 20);
					state = "Game";
					
				}
			}
			else easyText.setFillColor(sf::Color::White);
			if (this->hardText.getGlobalBounds().contains(this->mousePosition))
			{
				hardText.setFillColor(sf::Color::Yellow);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					
					delete game;
					game = new GameScreen(75, 75);
					state = "Game";

				}
			}
			else hardText.setFillColor(sf::Color::White);
			if (this->mediumText.getGlobalBounds().contains(this->mousePosition))
			{
				mediumText.setFillColor(sf::Color::Blue);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					delete game;
					game = new GameScreen(45, 45);
					state = "Game";

				}
			}
			else mediumText.setFillColor(sf::Color::White);
		}
	}
}

StartingScreen::StartingScreen(sf::RenderWindow& w)
{
	
	if (!font.loadFromFile("Fonts/sewer.ttf")) {
		std::cout << "Font not loaded\n";
		return;
	}
	chooseText.setFont(font);
	easyText.setFont(font);
	hardText.setFont(font);
	chooseText.setCharacterSize(40);
	easyText.setCharacterSize(30);
	hardText.setCharacterSize(30);
	chooseText.setString("Choose difficulty");
	easyText.setString("20x20");
	hardText.setString("70x70");
	chooseText.setFillColor(sf::Color::White);
	easyText.setFillColor(sf::Color::White);
	hardText.setFillColor(sf::Color::White);
	chooseText.setPosition(sf::Vector2f(w.getSize().x / 2-chooseText.getGlobalBounds().width/2, w.getSize().y / 2 - 200));
	
	mediumText.setFont(font);
	mediumText.setCharacterSize(30);
	mediumText.setString("45x45");

	easyText.setPosition(sf::Vector2f(w.getSize().x / 2 - 200, w.getSize().y / 2));
	mediumText.setPosition(sf::Vector2f(w.getSize().x / 2 - 0, w.getSize().y/2));
	
	hardText.setPosition(sf::Vector2f(w.getSize().x / 2 + 200, w.getSize().y/2));
	
}
