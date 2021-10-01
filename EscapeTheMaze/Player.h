#pragma once
#include "libraries.h"
class Player
{
	sf::Texture* playerTexture;
	
	sf::RectangleShape rect;
	float moveSpeed;
	bool shouldItMove(const std::vector<sf::RectangleShape>&, float, float);

	sf::RectangleShape lastCell;
public:
	sf::Sprite body;
	void render(sf::RenderWindow&);
	void update(const std::vector<sf::RectangleShape>&);
	sf::Vector2f getPlayerCenter();
	Player();
	~Player();
};


