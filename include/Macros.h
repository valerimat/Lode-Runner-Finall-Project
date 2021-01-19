#pragma once

enum class IQ
{
	Smart,
	Random,
	OneSide,
};

enum class Color
{
	White,
	Grey,
	Black,
};


enum class States
{
	Win,
	InGameMenu,
	MainMenu,
	Play,
	Death,
	Exit,
	Continue,
	Settings,
	ResetLevel,
	Scoreboard,
};

enum class NextStep
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE,
};
const int BASE_LIVES = 3;
const int OFFSET = 50 * 0.8;
const float STEP = 1.2f;

const char PLAYER = char('@');
const char COIN = char('*');
const char PRESENT = char('P');
const char ENEMY = char('%');
const char POLE = char('-');
const char GROUND = char('#');
const char LADDER = char('H');
const char NONE = char(' ');
const char WALL = char('w');



const int LADDER_INT = 1;
const int ROPE_INT = 2;
const int PLATFROM_INT = 3;
const int AIR_INT = 4;
const int PLAYER_INT = 5;
const int GROUND_INT = 6;

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
#define PRESENT_TEXTURE 9
#define MAAKE_TEXTURE 10
#define ZEVEL_TEXTURE 11
#define SHOP_TEXTURE 12