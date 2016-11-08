#include "MaRect.h"
using namespace std;

class Player {
private:
	static const int paddleSpeed = 300;
public:
	static float CheckInputP1() {
		/*if (Keyboard::isKeyPressed(Keyboard::Up)) return Vector2f(0, -paddleSpeed);
		else if (Keyboard::isKeyPressed(Keyboard::Down)) return Vector2f(0, paddleSpeed);
		else return Vector2f(0, 0);*/
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

	MaRect::MaRect(Vector2f pos, float thic, float length, Ball* b) {
		rect = new sf::RectangleShape(Vector2f(thic, length));
		rect->setFillColor(sf::Color::Blue);
		hereIStart = pos;
		HardReset();
		font.loadFromFile("arial.ttf");
		text.setFillColor(Color::Red);
		text.setFont(font);
		text.setCharacterSize(50);
		ball = b;
		paddleSpeed = PADDLE_SPEED;
	}

	void MaRect::Reset() {
		rect->setPosition(hereIStart);
	}
	void MaRect::HardReset() {
		rect->setPosition(hereIStart);
		SetScore(0);
	}
	void MaRect::SetScore(int value) {
		score = value;
		text.setString(to_string(score));
	}
	void MaRect::IncrementScore() {
		score++;
		text.setString(to_string(score));
	}

	void MaRect::Update(float dt) {//todo if if if if button pressed i tede
		this->velocity = Vector2f(0, paddleSpeed * Player::CheckInputP1());//Player::CheckInputP1();
		Vector2f tempPos = rect->getPosition();
		tempPos += velocity*dt;
		if (tempPos.y <= 0 || tempPos.y + rect->getSize().y > 600)
			return;
		rect->setPosition(tempPos);
		if(CheckCollision(ball))
			ball->BounceOff(rect->getPosition().y + PADDLE_LENGTH / 2);
		
	}

	int MaRect::GetScore() {
		return score;
	}

	void MaRect::Win() {
		text.setString("Winner");
	}
	void MaRect::Loose() {
		text.setString("Looser");
	}
	void MaRect::Render(RenderWindow* window) {
		window->draw(*rect);
		text.setPosition(rect->getPosition());
		window->draw(text);
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

