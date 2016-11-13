#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"
//static const float SCREEN_WIDTH =  800;
//static const float SCREEN_HEIGHT = 600;
//static const float PADDLE_THICKNESS = 30.f;
//static const float PADDLE_LENGTH = 100.f;
//static const float PADDLE_SPEED = 300.f;
//static const float BLOCK_LENGTH = 200.f;
//static const float BLOCK_THICKNESS = 30.f;
//static const int BALL_RADIUS = 10;
using namespace sf;
class MaShape { 
public:
//	Vector2f velocity;
	virtual void render(RenderWindow* wind)=0;
	virtual void update(float dt)=0;
	
};