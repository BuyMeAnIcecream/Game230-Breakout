#pragma once
#include "MaShape.h"
#include "Ball.h"
class MaRect :public MaShape {
private:
	int score;
	Vector2f hereIStart;
	Font font;
	Ball* ball;
	bool CheckCollision(Ball* b);
	Vector2f velocity;
	float paddleSpeed;
public:
	Text text;
	RectangleShape* rect;
	MaRect(Vector2f pos, float thic, float length, Ball* b);
	void Reset();
	void HardReset();
	void SetScore(int value);
	void IncrementScore();
	void Update(float dt);
	int GetScore();
	void Win();
	void Loose();
	void Render(RenderWindow* window);
	
};