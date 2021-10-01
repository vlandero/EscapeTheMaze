#pragma once
#include "libraries.h"
#include "StartingScreen.h"
#include <string>

class Game
{
	std::string windowState; //Starting and Game
	sf::RenderWindow* window;
	void render();
	void update();
	void pollEvents();

	sf::Vector2i mouseProv;
	sf::Vector2f mousePosition;
	void setMousePosition();

	StartingScreen* startingScreen;
	GameScreen* gameScreen;

public:
	Game();
	~Game();
	
	void run();
};

