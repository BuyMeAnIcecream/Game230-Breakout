
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
	Ball* ball2;
	MaRect* pad1;
	MaRect* pad2;
	RenderWindow* window;
	Text text;
	
	/*GameManager(Ball* b, Ball*b2, MaRect* p1, MaRect* p2, RenderWindow* win_sound) {*/
	GameManager(Ball* b, MaRect* p1) {
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

	bool anybodyAlive() {
		if (pad1 == NULL && pad2 == NULL)
			return true;
	};

	bool checkWin(int objectsLeft) {
		if (objectsLeft < 2) return true;
		return false;
	}

	bool checkLoose() {
		if (pad1 == NULL) return true;
		return false;
	}

/*
	void CheckWin() {

		if (pad1->GetScore() > 4) {
			//pad1->Win();
			//pad2->Loose();
			Text t;
			Font font;
			font.loadFromFile("arial.ttf");
			t.setFillColor(Color::Red);
			t.setFont(font);
			t.setCharacterSize(50);
			t.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			t.setString("player2 wins");
			window->draw(t);
			pressToRestart = true;

		}
		if (pad2->GetScore() > 4) {
			//pad2->Win();
			//pad1->Loose();
			Text t;
			Font font;
			font.loadFromFile("arial.ttf");
			t.setFillColor(Color::Red);
			t.setFont(font);
			t.setCharacterSize(50);
			t.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			t.setString("player1 wins");
			window->draw(t);
			pressToRestart = true;
		}

	}

	void PreRestart() {
		if (pad1->GetScore() > 4) {
			ball2->reset();
			ball->reset();
			pad1->HardReset();
			pad2->HardReset();
			while (!Keyboard::isKeyPressed(Keyboard::Space)) {
				sf::Event event;
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window->close();
				}
			}

			pressToRestart = false;
		}
		if (pad2->GetScore() > 4) {
			ball2->reset();
			ball->reset();
			pad1->HardReset();
			pad2->HardReset();
			pressToRestart = false;
			while (!Keyboard::isKeyPressed(Keyboard::Space)) {
				sf::Event event;
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window->close();
				}
			}

		}
	}
	void BallWhereAreYou() {
		if (ball->getPosition().x < 0 || ball2->getPosition().x < 0) {
			ball->reset();
			ball2->reset();
			pad1->reset();
			pad2->reset();
			pad1->IncrementScore();
		}
		if (ball->getPosition().x > SCREEN_WIDTH || ball2->getPosition().x>  SCREEN_WIDTH)
		{
			ball->reset();
			ball2->reset();
			pad1->reset();
			pad2->reset();
			pad2->IncrementScore();
		}
	}
	*/
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

void buildLevel(int number){
for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 3+number; j++) {
		if (rand() % 5 + number > 3) {
			unique_ptr<Block> block(new Block(Vector2f(100 * i, 50 * j), b, &weak));
			blocks.push_back(std::move(block));
		}                        //DID I FUCK UP HERE?
		else {
			unique_ptr<Block> block(new Block(Vector2f(100 * i, 50 * j), b, &hard));
			blocks.push_back(std::move(block));
		}
	}
	}
}


int main()
{
	font.loadFromFile("arial.ttf");
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
	
	Paddle* p1 = new Paddle(Vector2f(SCREEN_WIDTH/2 , SCREEN_HEIGHT - PADDLE_THICKNESS),  PADDLE_LENGTH, PADDLE_THICKNESS, b, new Player(3, &font));
	//BlockType* weakBlock = new BlockType; 

	initialiseBlockTypes();
	//Block* block = new Block(Vector2f(BLOCK_LENGTH, BLOCK_THICKNESS), 100, 50, b, 1);


//	Block::loadBrickSounds();
	loadSounds();


	//INIT BLOCK TYPES
	

	buildLevel(1);

	//GameManager* gm = new GameManager(b, b2, p1, p2, &window);
	Clock clock;
	GameManager* gm = new GameManager(b,p1);
//	vector<MaShape*> sceneObjects;
	

	unique_ptr<Block> bl ( new Block(Vector2f(100 , 50 ), b, &weak));
	
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
			if (blocks[i]->endMyLife)
				blocks.erase(remove(blocks.begin(), blocks.end(), blocks[i]),blocks.end());
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

		if (gm->checkLoose())
			cout << "endspiel";
		/*
		if (gm->pressToRestart) {
			gm->PreRestart();
			clock.restart().asSeconds();
		}
		*/

	}
	return 0;
}

