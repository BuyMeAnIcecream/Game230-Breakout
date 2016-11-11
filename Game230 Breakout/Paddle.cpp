#include "Paddle.h"

class Player {
private:
	static const int paddleSpeed = 300;
public:
	static float CheckInputP1() {
		if (Keyboard::isKeyPressed(Keyboard::Up)) return -1;
		else if (Keyboard::isKeyPressed(Keyboard::Down)) return 1;
		else return 0;
	}
	static Vector2f CheckInputP2() { //There is a nice Command pattern, which I ,sadly,have no time to implement

		if (Keyboard::isKeyPressed(Keyboard::W)) return Vector2f(0, -paddleSpeed);
		else if (Keyboard::isKeyPressed(Keyboard::S)) return Vector2f(0, paddleSpeed);
		else return Vector2f(0, 0);
	}
};
Paddle::Paddle(Vector2f pos, float thic, float length, Ball* b):MaRect::MaRect(pos, thic, length, b) {
	
	hereIStart = pos;
}
void Paddle::Update(float dt) {
	this->velocity = Vector2f(0, paddleSpeed * Player::CheckInputP1());//Player::CheckInputP1();
	Vector2f tempPos = rect->getPosition();
	tempPos += velocity*dt;
	if (tempPos.y <= 0 || tempPos.y + rect->getSize().y > 600)
		return;
	rect->setPosition(tempPos);
	if (CheckCollision(ball))
		ball->BounceOff(rect->getPosition().y + PADDLE_LENGTH / 2);
}
void Paddle::Reset() {
	rect->setPosition(hereIStart);
}



