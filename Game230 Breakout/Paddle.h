#pragma once
#include  "MaRect.h"
#include "Player.h"
class Paddle: public MaRect {
private:
	Vector2f hereIStart;
	Player* player;
	void updateHealthText(Vector2f position);
public:
	Paddle(Vector2f pos, float thic, float length, Ball* b, Player* p);
	void MaRect::update(float dt);
	void reset();
	//void holdABall();
	friend void Ball::stayHere(Vector2f position);
	friend void Ball::sendFlying();
	void Paddle::render(RenderWindow* window);
//	void MaRect::render(RenderWindow* window);
};