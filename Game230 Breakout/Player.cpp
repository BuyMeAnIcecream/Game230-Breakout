#include "Player.h"

using namespace sf;

Player::Player(int health, Font* font)
{
	lives = health;
	score = 0;
	isAlive = true;
	
	t.setFont(*font);
	
//	t.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
}

Player::~Player()
{
	//delete t;
}

void Player::looseHealth()
{
	lives--;
	if (lives < 0)
		isAlive = false;
}

void Player::displayHealth(sf::Vector2f position)
{
	t.setFillColor(Color::Red);
	t.setCharacterSize(50);
	t.setString(std::to_string(lives));
	t.setPosition(position);
}
