#include "Block.h";

void Block::update(float dt) {
	if (checkCollision(ball)) {
		ball->bounceOffBlock(rect);
		takeDamage(1);
	}
	//	ball->BounceOff(rect->getPosition().y + PADDLE_LENGTH / 2);      TODO flip direction
}

Block::Block(Vector2f pos, Ball* b,/*, float thic, float length,  int health*/BlockType* bt):MaRect::MaRect(pos,  bt->length, bt->thickness, b) {
	this->health = bt->health;
//	texture1 = bt->texture1;
	endMyLife = false;
	rect->setPosition(pos);
//	rect->setTexture(&bt->texture1);
	texture1 = &bt->texture1;
	texture2 = &bt->texture2;
	updateTexture();

	rect->setFillColor(bt->color);
}

Block::~Block()
{
	//todo
}

void Block::updateTexture()
{
	if (health == 1)
		rect->setTexture(texture1);
	if (health == 2)
		rect->setTexture(texture2);
}

void Block::crack()
{
	crack_sound.play();
}

void Block::destroy()
{
	destroy_sound.play();
}


void Block::takeDamage(int d) {
	health -= d;
	updateTexture();
	if (health <= 0) {
		ball->score++;
		endMyLife = true;
		destroy();
		return;
	}
	crack();

}

extern BlockType weak;
extern BlockType hard;

