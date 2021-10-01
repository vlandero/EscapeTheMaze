#include "Game.h"


void Game::setMousePosition()
{
	mouseProv = sf::Mouse::getPosition(*this->window);
	this->mousePosition = this->window->mapPixelToCoords(this->mouseProv);
}

Game::Game()
{
	
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "MazeRunner", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	windowState = "Starting";
	startingScreen = new StartingScreen(*this->window);
	gameScreen = new GameScreen(0, 0);
}

Game::~Game()
{
	delete this->window;
}

void Game::render()
{
	this->window->clear();

	this->startingScreen->render(*this->window, windowState);
	this->gameScreen->render(*this->window, windowState);

	this->window->display();
}

void Game::update()
{
	this->pollEvents();
	this->startingScreen->update(*this->window,this->gameScreen, windowState);
	this->gameScreen->update(*this->window, windowState);
	//this->congrats->update(*this->window, *this->startingScreen);
}

void Game::pollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			this->window->close();
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}
