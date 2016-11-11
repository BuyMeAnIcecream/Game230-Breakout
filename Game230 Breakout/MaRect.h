#pragma once
#include "MaShape.h"
#include "Ball.h"
class MaRect :public MaShape {
protected:
//	int score;
	Ball* ball;
	bool CheckCollision(Ball* b);
	Vector2f velocity;
	float paddleSpeed;
public:
	RectangleShape* rect;
	MaRect(Vector2f pos, float thic, float length, Ball* b);
//	void Reset();
	virtual void Update(float dt) =0;
	void Render(RenderWindow* window);
	
};