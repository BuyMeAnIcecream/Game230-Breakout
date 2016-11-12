#include "Ball.h"
using namespace std;
static const float BALL_VELOCITY = 400.f;
static const int BALL_RADIUS = 10;
	Ball::Ball() {
		circle = new sf::CircleShape(BALL_RADIUS);
		circle->setFillColor(sf::Color::Red);
		circle->setOrigin(Vector2f(circle->getRadius(), circle->getRadius()));
		vel = BALL_VELOCITY;
//		direction = randomizeAngle();
		srand(time(NULL));
//		p1 = pad1;
//		p2 = pad2;
//		brick = br;
		reset();
		texture.loadFromFile("ball.png");
		circle->setTexture(&texture);
		buf.loadFromFile("bounce.ogg");
		sound.setBuffer(buf);
	}
	
	Vector2f Ball::getPosition() {
		return circle->getPosition();
	}
		void Ball::update(float dt) {
		checkBorders();
		Vector2f tempPos = getPosition();
		tempPos.x += direction.x*vel*dt;
		tempPos.y += direction.y*vel*dt;
		if (!sited) {
			circle->setPosition(tempPos);
			return;
		}
		//   LISTEN TO INPUT IF SPACE -
		if (space)
			sited = false;
		
	}


	
	void Ball::render(sf::RenderWindow* wind) {
		wind->draw(*circle);
	}
	void Ball::reset() {
		circle->setPosition(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		
//		direction = randomizeAngle();
		sited = true;
	}
	void Ball::checkBorders() {
		if (GetGlobalBounds().top <= 0) {
			flipYVel();
			sound.play();
		}
		/*if (circle->getGlobalBounds().top + circle->getGlobalBounds().height >= SCREEN_HEIGHT) {
			flipYVel();
			sound.play();
		}*/
		if (GetGlobalBounds().left <= 0) {
			flipXVel();
			sound.play();
		}

		if (GetGlobalBounds().left + GetGlobalBounds().width >= SCREEN_WIDTH) {
			flipXVel();
			sound.play();
		}

	}

	FloatRect Ball::GetGlobalBounds() {
		return circle->getGlobalBounds();
	}
	

	void Ball::bounceOffPaddle(/*float padCenterY*/ float padCenterX) {
		/*float yDifference = padCenterY - getPosition().y;
		float yRatio = yDifference / (PADDLE_LENGTH / 2);
		direction.y = -yRatio;
		flipXVel();*/
		float xDifference = padCenterX - getPosition().x;
		float xRatio = xDifference / (PADDLE_LENGTH / 2);
		direction.x = -xRatio;
		flipYVel();
		sound.play();
	}

	void Ball::bounceOffBlock(RectangleShape* rs) {
		if (rs->getPosition().x + BLOCK_LENGTH <= this->getPosition().x) flipXVel();
		else if (rs->getPosition().x >= this->getPosition().x) flipXVel();
		else flipYVel();
		sound.play();
	}
	void Ball::flipYVel() {
		direction.y = -direction.y;
	}
	void Ball::flipXVel() {
		direction.x = -direction.x;
	}

	Vector2f Ball::randomizeAngle() {
		float Xvel;
		float Yvel;
		Yvel = rand() % (90 - 70 + 1) + 70;
		Xvel= 100 - Yvel;
		if (rand() % 2 > 0) //0or1
			Xvel = -Xvel;
//		cout << Xvel/100.f << " " << Yvel/100.f;
		return Vector2f(Xvel/100.f, Yvel/100.f);

	}
