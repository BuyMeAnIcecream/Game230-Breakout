#include "MaRect.h"
using namespace std;



	MaRect::MaRect(Vector2f pos, float thic, float length, Ball* b) {
		rect = new sf::RectangleShape(Vector2f(thic, length));
		rect->setFillColor(sf::Color::Blue);
		rect->setPosition(pos);
		ball = b;
		paddleSpeed = PADDLE_SPEED;
	}


		/*																				//THIS GOES TO BRICK!!!
    void MaRect::Update(float dt) {	
		if(CheckCollision(ball))
			ball->BounceOff(rect->getPosition().y + PADDLE_LENGTH / 2);
	}
	*/
	void MaRect::Render(RenderWindow* window) {
		window->draw(*rect);
	}
	
	bool MaRect::CheckCollision(Ball* b) {
		if (rect->getGlobalBounds().intersects(b->GetGlobalBounds()))
			return true;
		return false;
	}
	
	/*
	class StupidAI {
	public:
		static float WhereDoIGo(Ball* b, Ball* b2, Paddle* p) {
			if (b->getPosition().x < b2->getPosition().x) {
				if (b->getPosition().y > p->rect->getPosition().y + PADDLE_LENGTH / 2)
					return paddleSpeed;
				else
					return -paddleSpeed;
			}
			else
				if (b2->getPosition().y > p->rect->getPosition().y + PADDLE_LENGTH / 2)
					return paddleSpeed;
				else
					return -paddleSpeed;
		}
	};
	*/

