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
	void load();
	void load_stable();
	void load_level_digits();
	void load_score_digits();
	void load_time_digits();
	void load_lives_digits();

	void draw_score(sf::RenderWindow& window);
	void draw_lives(sf::RenderWindow& window);
	void draw_level(sf::RenderWindow& window);
	void draw_time(sf::RenderWindow& window);

	std::vector<std::unique_ptr <sf::Texture>> m_textures;
	std::vector < std::unique_ptr<sf::Sprite>> m_stable;
	std::vector < std::unique_ptr<sf::Sprite>> lives_digits;
	std::vector < std::unique_ptr<sf::Sprite>> score_digits;
	std::vector < std::unique_ptr<sf::Sprite>> time_digits;
	std::vector < std::unique_ptr<sf::Sprite>> level_digits;

	int m_number_of_level;

	int m_lives;
	
	Score * m_score;
	Clock * m_clock;

	int *m_time;
};