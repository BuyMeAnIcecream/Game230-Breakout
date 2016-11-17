#include "Paddle.h"

class PlayerControl {
private:
	static const int paddleSpeed = 300;
public:
	static float checkControlInputP1() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) return -1;
		else if (Keyboard::isKeyPressed(Keyboard::Right)) return 1;
		//else if (Keyboard::isKeyPressed(Keyboard::Space)) return 2;	
		else return 0;
	}
	static bool checkActionButton() {
		if (Keyboard::isKeyPressed(Keyboard::Space))
			return true;
		else
			return false;
	}

	static Vector2f CheckInputP2() { //There is a nice Command pattern, which I ,sadly,have no time to implement

		if (Keyboard::isKeyPressed(Keyboard::A)) return Vector2f(0, -paddleSpeed);
		else if (Keyboard::isKeyPressed(Keyboard::D)) return Vector2f(0, paddleSpeed);
		else return Vector2f(0, 0);
	}
};
Paddle::Paddle(Vector2f pos, float thic, float length, Ball* b, Player* p):MaRect::MaRect(pos, thic, length, b) {
	player = p;
	hereIStart = pos;
	rect->setFillColor(sf::Color::Blue);
}
void Paddle::update(float dt) {
	this->velocity = Vector2f( paddleSpeed * PlayerControl::checkControlInputP1(),0);//PlayerControl::checkControlInputP1();
	Vector2f tempPos = rect->getPosition();
	tempPos += velocity*dt;
	if (tempPos.x <= 0 || tempPos.x + rect->getSize().x > SCREEN_WIDTH)
		return;
	//detect collision
	rect->setPosition(tempPos);
	if (checkCollision(ball)) {
		ball->bounceOffPaddle(rect->getPosition().x + PADDLE_LENGTH / 2);
		ball->lastHitBy = this->player;
	}
	
	if (ball->sited && PlayerControl::checkActionButton()) {
		ball->sendFlying();
		
	}
	if (ball->sited) {
		ball->stayHere(Vector2f(rect->getPosition().x + PADDLE_LENGTH / 2, rect->getPosition().y - BALL_RADIUS));
		ball->lastHitBy = this->player;
	}
	player->updateHealthText(Vector2f(rect->getPosition().x + PADDLE_LENGTH / 2, rect->getPosition().y - PADDLE_THICKNESS / 2));
}

void Paddle::render(RenderWindow* window) {
	window->draw(*rect);
	//std::cout << "here";
    window->draw(player->t);
} 


void Paddle::reset() {
	rect->setPosition(hereIStart);
}

void Ball::stayHere(Vector2f position) {
	circle->setPosition(position);
}

void Ball::sendFlying() {
	sited = false;
	direction.y = 1;
	direction.x = 0;
}


