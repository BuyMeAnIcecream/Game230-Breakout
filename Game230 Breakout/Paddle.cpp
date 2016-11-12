#include "Paddle.h"

class Player {
private:
	static const int paddleSpeed = 300;
public:
	static float CheckInputP1() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) return -1;
		else if (Keyboard::isKeyPressed(Keyboard::Right)) return 1;
		else return 0;
	}
	static Vector2f CheckInputP2() { //There is a nice Command pattern, which I ,sadly,have no time to implement

		if (Keyboard::isKeyPressed(Keyboard::A)) return Vector2f(0, -paddleSpeed);
		else if (Keyboard::isKeyPressed(Keyboard::D)) return Vector2f(0, paddleSpeed);
		else return Vector2f(0, 0);
	}
};
Paddle::Paddle(Vector2f pos, float thic, float length, Ball* b):MaRect::MaRect(pos, thic, length, b) {	
	hereIStart = pos;
}
void Paddle::update(float dt) {
	this->velocity = Vector2f( paddleSpeed * Player::CheckInputP1(),0);//Player::CheckInputP1();
	Vector2f tempPos = rect->getPosition();
	tempPos += velocity*dt;
	if (tempPos.x <= 0 || tempPos.x + rect->getSize().x > SCREEN_WIDTH)
		return;
	//detect collision
	rect->setPosition(tempPos);
	if (checkCollision(ball))
		ball->bounceOffPaddle(rect->getPosition().x + PADDLE_LENGTH / 2);
}
void Paddle::reset() {
	rect->setPosition(hereIStart);
}



