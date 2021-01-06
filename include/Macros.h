#pragma once

enum class IQ
{
	Smart,
	Random,
	OneSide,
};

enum class State
{
	Main,
	Game,
	End,
};

enum class NextStep
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE,
};

const int OFFSET = 50 * 0.8;
const float STEP = 1;

const char PLAYER = char('@');
const char COIN = char('*');
const char ENEMY = char('%');
const char POLE = char('-');
const char GROUND = char('#');
const char LADDER = char('H');
const char NONE = char(' ');
const char WALL = char('w');
const int SIZE_OF_TILE = 40;

#define HEIGHT 850
#define WIDTH  800

#define LADDER_TEXTURE 0
#define GROUND_TEXTURE 1
#define PLAYER_TEXTURE 2
#define POLE_TEXTURE 3
#define ENEMY_TEXTURE 4
#define COIN_TEXTURE 5
#define NONE_TEXTURE 6
#define BACKGROUND_TEXTURE 7
#define GROUND_W_SIGNS_TEXTURE 8