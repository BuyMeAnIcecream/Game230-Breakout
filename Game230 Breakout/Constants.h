#pragma once
#include "SFML/Window.hpp"
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
static const float SCREEN_WIDTH = 800;
static const float SCREEN_HEIGHT = 600;
static const float PADDLE_THICKNESS = 30.f;
static const float PADDLE_LENGTH = 100.f;
static const float PADDLE_SPEED = 300.f;
static const float BLOCK_LENGTH = 60.f;
static const float BLOCK_THICKNESS = 20.f;
static const int BALL_RADIUS = 10;

//static const int WEAK_BLOCK_HEALTH= 1;



extern sf::Font font;
extern sf::Sound crack_sound;
extern sf::SoundBuffer crack_sb;
extern sf::Sound destroy_sound;
extern sf::SoundBuffer destroy_sb;
extern sf::Sound paddle_hit;
extern sf::SoundBuffer pedalt_hit_sb;
extern sf::Sound wall_hit;
extern sf::SoundBuffer wall_hit_sb;
extern sf::Sound win_sound;
extern sf::SoundBuffer win_sb;
extern sf::Sound loose_hp_sound;
extern sf::SoundBuffer loose_hp_sb;

