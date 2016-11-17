#pragma once

//#include "Paddle.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include "MaShape.h"
#include "Player.h"
//#include "Paddle.h"
class Ball :public MaShape {
private:
	CircleShape* circle;
	Vector2f position;
	Texture texture1;
	SoundBuffer buf;
	Sound sound;
	float vel;
	Vector2f direction;
	void whereAmI();
	
public:
	int score;
	Player* lastHitBy;
	bool sited;
	FloatRect GetGlobalBounds();
	Ball();
	void update(float dt);
	Vector2f getPosition();
	void render(sf::RenderWindow* wind);
	void reset();
	void bounceOffPaddle(float padCenterY);
	void checkBorders();
//	void CheckPaddle(Paddle * p);
	void flipYVel();
	void flipXVel();
	Vector2f randomizeAngle();
	void bounceOffBlock(RectangleShape* rs);
	//void sitOnThePaddle(Paddle p);
	void stayHere(Vector2f position);
	void sendFlying();
	void speedUp();
};