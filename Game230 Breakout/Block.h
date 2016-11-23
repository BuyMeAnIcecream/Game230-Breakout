#pragma once
#include "MaRect.h"

struct BlockType {
	Texture texture1;
	Texture texture2;
	int health;
	float thickness;
	float length;
	Color color;
};
class Block : public MaRect {

private:
	
	Texture* texture1;
	Texture* texture2;
	int health;
	
	Color color;
	
public:
	

	bool endMyLife;
	void takeDamage(int d);
	Block(Vector2f pos, Ball* b, BlockType* bt);
	~Block();
	void MaRect::update(float dt);
	void updateTexture();
	void crack();
	void destroy();
	bool operator ==(const Block &b);

//	static void loadBrickSounds();
		
};

