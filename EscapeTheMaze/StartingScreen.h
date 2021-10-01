#pragma once
#include "libraries.h"
#include "GameScreen.h"
class StartingScreen
{
	sf::Font font;
	
	sf::Vector2i mouseProv;
	sf::Vector2f mousePosition;
	sf::Text chooseText;
	sf::Text easyText;
	sf::Text mediumText;
	sf::Text hardText;

public:
	void render(sf::RenderWindow&, std::string&);
	void update(sf::RenderWindow&, GameScreen*&, std::string&);
	StartingScreen(sf::RenderWindow&);
};

