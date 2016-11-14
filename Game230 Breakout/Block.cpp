#include "Block.h";

void Block::update(float dt) {
	if (checkCollision(ball)) {
		ball->bounceOffBlock(rect);
		takeDamage(1);
	}
	//	ball->BounceOff(rect->getPosition().y + PADDLE_LENGTH / 2);      TODO flip direction
}

Block::Block(Vector2f pos, float thic, float length, Ball* b, int health):MaRect::MaRect(pos, thic, length, b) {
	this->health = health;
	rect->setPosition(pos);
}

void Block::takeDamage(int d) {
	health -= d;
}