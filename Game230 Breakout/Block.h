#pragma once
#include "MaRect.h"
class Block : public MaRect {
private:
	int health;
	bool endMyLife;
public:
	void takeDamage(int d);
	Block(Vector2f pos, float thic, float length, Ball* b, int health);
	void MaRect::update(float dt);

};