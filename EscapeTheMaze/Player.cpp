#include "libraries.h"
#include "Player.h"

bool Player::shouldItMove(const std::vector<sf::RectangleShape>&wallArr,float dx,float dy)
{
	int n = wallArr.size();
	sf::FloatRect playerBounds = body.getGlobalBounds();
	sf::FloatRect wallBounds;
	sf::FloatRect nextPos = playerBounds;
	for (int i = 0; i < n; ++i) {
		wallBounds = wallArr[i].getGlobalBounds();
		nextPos = playerBounds;
		nextPos.left += dx;
		nextPos.top += dy;
		if (nextPos.left < 0 || nextPos.top < 0)
			return false;
		if (wallBounds.intersects(nextPos))
			return false;
	}
	return true;
}

void Player::render(sf::RenderWindow& target)
{
	target.draw(body);
}

void Player::update(const std::vector<sf::RectangleShape>&wallArr)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (shouldItMove(wallArr, -1.f * moveSpeed, 0.f))
			body.move(-1.f * moveSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (shouldItMove(wallArr, 1.f * moveSpeed, 0.f))
			body.move(1.f * moveSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (shouldItMove(wallArr, 0.f,-1.f*moveSpeed))
			body.move(0.f,-1.f*moveSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (shouldItMove(wallArr, 0.f, 1.f * moveSpeed))
			body.move(0.f, 1.f * moveSpeed);
	}
}

sf::Vector2f Player::getPlayerCenter()
{
	return sf::Vector2f(body.getGlobalBounds().left + body.getGlobalBounds().width / 2, body.getGlobalBounds().top + body.getGlobalBounds().height / 2);
}

Player::Player()
{
	moveSpeed = 2.f;
	playerTexture = new sf::Texture;
	if (!playerTexture->loadFromFile("Player/idle.png")) {
		std::cout << "Textures not loaded";
		return;
	}
	playerTexture->setSmooth(true);
	
	body.setTexture(*playerTexture);
	body.setScale(.1f, .1f);
	rect.setFillColor(sf::Color::Cyan);
	rect.setSize(sf::Vector2f(100.f, 100.f));
	rect.setPosition(sf::Vector2f(20.f, 20.f));
}

Player::~Player()
{
	delete playerTexture;
}
