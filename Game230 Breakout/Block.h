#pragma once
#include "MaRect.h"


static Sound sound;
static SoundBuffer sb;
struct BlockType {
	Texture texture1;
	Texture texture2;
	int health;
	float thickness;
	float length;
	
};
class Block : public MaRect {

private:
	static Sound sound;
	Texture* texture1;
	Texture* texture2;
	int health;
	bool endMyLife;
	
	
public:
	void takeDamage(int d);
	Block(Vector2f pos, Ball* b,/* float thic, float length, int health*/ BlockType* bt);
	~Block();
	void MaRect::update(float dt);
	void updateTexture();
};