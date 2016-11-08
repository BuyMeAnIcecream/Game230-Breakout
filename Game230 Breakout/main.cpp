
#include <vector>
#include "MaRect.h"

#include <random>
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;
using namespace std;



class GameManager {
public:
	bool pressToRestart;
	Ball* ball;
	Ball* ball2;
	MaRect* pad1;
	MaRect* pad2;
	RenderWindow* window;
	GameManager(Ball* b, Ball*b2, MaRect* p1, MaRect* p2, RenderWindow* win) {
		ball = b;
		ball2 = b2;
		pad1 = p1;
		pad2 = p2;
		window = win;
		pressToRestart = false;
	}

	void CheckWin() {

		if (pad1->GetScore() > 4) {
			//pad1->Win();
			//pad2->Loose();
			Text t;
			Font font;
			font.loadFromFile("arial.ttf");
			t.setFillColor(Color::Red);
			t.setFont(font);
			t.setCharacterSize(50);
			t.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			t.setString("player2 wins");
			window->draw(t);
			pressToRestart = true;

		}
		if (pad2->GetScore() > 4) {
			//pad2->Win();
			//pad1->Loose();
			Text t;
			Font font;
			font.loadFromFile("arial.ttf");
			t.setFillColor(Color::Red);
			t.setFont(font);
			t.setCharacterSize(50);
			t.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			t.setString("player1 wins");
			window->draw(t);
			pressToRestart = true;
		}

	}

	void PreRestart() {
		if (pad1->GetScore() > 4) {
			ball2->Reset();
			ball->Reset();
			pad1->HardReset();
			pad2->HardReset();
			while (!Keyboard::isKeyPressed(Keyboard::Space)) {
				sf::Event event;
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window->close();
				}
			}

			pressToRestart = false;
		}
		if (pad2->GetScore() > 4) {
			ball2->Reset();
			ball->Reset();
			pad1->HardReset();
			pad2->HardReset();
			pressToRestart = false;
			while (!Keyboard::isKeyPressed(Keyboard::Space)) {
				sf::Event event;
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window->close();
				}
			}

		}
	}
	void BallWhereAreYou() {
		if (ball->getPosition().x < 0 || ball2->getPosition().x < 0) {
			ball->Reset();
			ball2->Reset();
			pad1->Reset();
			pad2->Reset();
			pad1->IncrementScore();
		}
		if (ball->getPosition().x > SCREEN_WIDTH || ball2->getPosition().x>  SCREEN_WIDTH)
		{
			ball->Reset();
			ball2->Reset();
			pad1->Reset();
			pad2->Reset();
			pad2->IncrementScore();
		}
	}
};





int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
	Ball* b = new Ball();
	MaRect* p1 = new MaRect(Vector2f(SCREEN_WIDTH - PADDLE_THICKNESS, SCREEN_HEIGHT / 2), PADDLE_THICKNESS, PADDLE_LENGTH, b);
	MaRect* p2 = new MaRect(Vector2f(0, SCREEN_HEIGHT / 2), PADDLE_THICKNESS, PADDLE_LENGTH, b);
	MaRect* brick = new MaRect(Vector2f(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5), PADDLE_THICKNESS, PADDLE_LENGTH, b);

	Ball* b2 = new Ball();
	GameManager* gm = new GameManager(b, b2, p1, p2, &window);
	Clock clock;
	vector<MaShape*> sceneObjects;
	sceneObjects.push_back(b);
	sceneObjects.push_back(p1);
	sceneObjects.push_back(p2);
	sceneObjects.push_back(brick);
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		float dt = clock.restart().asSeconds();
		//b->Update(dt);
		////		b2->Update(dt);
		//p1->Update(dt, Player::CheckInputP1());
		//brick->Update(dt, Vector2f(0.f, 0.f));
  //      p2->Update(dt, Vector2f(0, StupidAI::WhereDoIGo(b, b2, p2)));
		//
		//gm->BallWhereAreYou();
		//gm->CheckWin();
		//b->Render(&window);
		//b2->Render(&window);
		//p1->Render(&window);
		//p2->Render(&window);
		//brick->Render(&window);
		for each (MaShape* ms in sceneObjects)
		{
			ms->Update(dt);
			ms->Render(&window);
		}

		window.display();
		if (gm->pressToRestart) {
			gm->PreRestart();
			clock.restart().asSeconds();
		}

	}
	return 0;
}

