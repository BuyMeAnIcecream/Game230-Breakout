#pragma once
//#include <SFML/Network.hpp>
//#include <SFML/System.hpp>
//#include <SFML/OpenGL.hpp>
//#include <SFML/Main.hpp>
//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
class Player {
private:
	int lives;
	
	int score;
	Text t;
//	Font* font;
public:
	bool isAlive;
	Player(int health, Font* font);
	~Player();
	void looseHealth();
	void displayHealth(Vector2f position);
};