
#include <vector>
#include "Paddle.h"
#include "Block.h"
#include <random>
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <memory>

using namespace sf;
using namespace std;

sf::Font font;
sf::Sound crack_sound;
sf::SoundBuffer crack_sb;
sf::Sound destroy_sound;
sf::SoundBuffer destroy_sb;
sf::Sound paddle_hit;
sf::SoundBuffer pedalt_hit_sb;
sf::Sound wall_hit;
sf::SoundBuffer wall_hit_sb;
sf::Sound win_sound;
sf::SoundBuffer win_sb;
sf::Sound loose_hp_sound;
sf::SoundBuffer loose_hp_sb;


class GameManager {
public:
	bool pressToRestart;
	Ball* ball;
//	Ball* ball2;
	Paddle* pad1;
//	MaRect* pad2;
	RenderWindow* window;
	Text text;
	
	/*GameManager(Ball* b, Ball*b2, MaRect* p1, MaRect* p2, RenderWindow* win_sound) {*/
	GameManager(Ball* b, Paddle* p1) {
		ball = b;
		//ball2 = b2;
		pad1 = p1;
		//	pad2 = p2;
	//		window = win_sound;
	//		pressToRestart = false;
	
		text.setFont(font);
		text.setFillColor(Color::White);
		text.setCharacterSize(50);
		text.setPosition(Vector2f(100, 10));
		b->score = 0;
	}

	void reset() {
		ball->score = 0;
	}

	void displayScore(RenderWindow* window) {
		text.setString(to_string(ball->score));
		window->draw(text);
	}

	//bool anybodyAlive() {
	//	if (pad1 == NULL && pad2 == NULL)
	//		return true;
	//};

	bool checkWin(int objectsLeft) {
		if (objectsLeft < 2) return true;
		return false;
	}

	bool checkLoose() {
		if (!pad1->isAlive) return true;
		return false;
	}


};

static void loadSounds()
{

	crack_sb.loadFromFile("audio/crack.wav");
	crack_sound.setBuffer(crack_sb);
	destroy_sb.loadFromFile("audio/destroyl.wav");
	destroy_sound.setBuffer(destroy_sb);
	
	pedalt_hit_sb.loadFromFile("audio/hit_ball.wav"); 
	paddle_hit.setBuffer(pedalt_hit_sb);
	wall_hit_sb.loadFromFile("audio/hit_wall.wav");
	wall_hit.setBuffer(wall_hit_sb);
	win_sb.loadFromFile("audio/win.mp3");
	win_sound.setBuffer(win_sb);
	loose_hp_sb.loadFromFile("audio/lose.wav");
	loose_hp_sound.setBuffer(loose_hp_sb);

	//Block::crack_sb.loadFromFile("audio\crack.mp3");

}
BlockType weak;
BlockType hard;
static void initialiseBlockTypes() {
	weak.health = 1;
	weak.length = BLOCK_LENGTH;
	weak.thickness = BLOCK_THICKNESS;
	weak.color = Color::Magenta;
	weak.texture1.loadFromFile("broken_brick.png");
	weak.texture2.loadFromFile("brick.png");

	hard.health = 2;
	hard.length = BLOCK_LENGTH;
	hard.thickness = BLOCK_THICKNESS;
	hard.color = Color::Green;
	hard.texture1.loadFromFile("broken_brick.png");
	hard.texture2.loadFromFile("brick.png");
}
Ball* b = new Ball();
vector<unique_ptr<Block>> blocks;
int blockCount = 0;
void buildLevel(int number){
for (int i = 0; i < 8; i++) {
	for (int j = 0; j < 3+number; j++) {
		if (rand() % 5 + number > 3) {
			unique_ptr<Block> block(new Block(Vector2f(105 * i, 50 * j), b, &weak));
			blocks.push_back(std::move(block));
		}                        //DID I FUCK UP HERE?
		else {
			unique_ptr<Block> block(new Block(Vector2f(105 * i, 50 * j), b, &hard));
			blocks.push_back(std::move(block));
		}

		blockCount++;
	}
	}
}


int main()
{
	font.loadFromFile("arial.ttf");
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
	
	Paddle* p1 = new Paddle(Vector2f(SCREEN_WIDTH/2 , SCREEN_HEIGHT - PADDLE_THICKNESS),  PADDLE_LENGTH, PADDLE_THICKNESS, b, new Player(2, &font));
	//BlockType* weakBlock = new BlockType; 

	initialiseBlockTypes();
	//Block* block = new Block(Vector2f(BLOCK_LENGTH, BLOCK_THICKNESS), 100, 50, b, 1);


//	Block::loadBrickSounds();
	loadSounds();


	//INIT BLOCK TYPES
	//crack_sound.play();

	buildLevel(0);

	//GameManager* gm = new GameManager(b, b2, p1, p2, &window);
	Clock clock;
	GameManager* gm = new GameManager(b,p1);
//	vector<MaShape*> sceneObjects;
	

//	unique_ptr<Block> bl ( new Block(Vector2f(100 , 50 ), b, &weak));
	
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		float dt = clock.restart().asSeconds();

		/*for each (MaShape* ms in sceneObjects)
		{
			ms->update(dt);
			ms->render(&window);
		
		}*/

		for (int i = 0; i < blocks.size();i++) {
			if (blocks[i]->endMyLife) {
				blocks.erase(remove(blocks.begin(), blocks.end(), blocks[i]), blocks.end());
				blockCount--;
			}

			else {
				blocks[i]->update(dt);
				blocks[i]->render(&window);
			}
		}

		b->update(dt);
		b->render(&window);
		p1->update(dt);
		p1->render(&window);
		gm->displayScore(&window);
		
		window.display();

		if (gm->checkLoose()) {
			window.close();
		}
			
		if (gm->checkWin(blockCount+1)) {
			gm->ball->speedUp();
			gm->ball->reset();
			gm->pad1->reset();
			buildLevel(2);
			win_sound.play();
		}
		

	}
	return 0;
}

