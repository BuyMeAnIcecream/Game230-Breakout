#pragma once
#include  "MaRect.h"
class Paddle: public MaRect {
private:
	Vector2f hereIStart;

public:
	Paddle(Vector2f pos, float thic, float length, Ball* b);
	void MaRect::Update(float dt);
	void Reset();
//	void MaRect::Render(RenderWindow* window);
};