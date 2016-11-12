#pragma once
#include "MaShape.h"
#include "Ball.h"
class MaRect :public MaShape {
protected:
//	int score;
	Ball* ball;
	bool checkCollision(Ball* b);
	Vector2f velocity;
	float paddleSpeed;
public:
	RectangleShape* rect;
	MaRect(Vector2f pos, float thic, float length, Ball* b);
//	void reset();
	virtual void update(float dt) =0;
	void render(RenderWindow* window);
	
};