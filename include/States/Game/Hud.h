#pragma once
#include <SFML/Graphics.hpp>
#include "Clock.h"
#include "Score.h"

class Player;

class Hud
{
public:
	Hud();
	Hud(int lives, int num_of_level, int* time);
	void Draw(sf::RenderWindow& window);
	void set_score();
	void set_lives(int lives);
	void load_textures();
	void up_level();

private:

	void draw_score(sf::RenderWindow& window);
	void draw_lives(sf::RenderWindow& window);
	void draw_level(sf::RenderWindow& window);
	void draw_time(sf::RenderWindow& window);

	std::vector<std::shared_ptr <sf::Texture>> m_textures;

	int m_number_of_level;

	int m_lives;
	
	Score * m_score;
	Clock * m_clock;

	int *m_time;
};