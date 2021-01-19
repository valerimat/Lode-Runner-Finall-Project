#pragma once
#include <SFML/Graphics.hpp>
#include "Clock.h"
#include "Score.h"

class Player;

class Hud
{
public:
	Hud();
	Hud(Player* player, int num_of_level, int *time);
	void Draw(sf::RenderWindow& window);
	void SetScore();
	void SetLives();
	void LoadTextures();
	void up_level();

private:

	void DrawScore(sf::RenderWindow& window);
	void DrawLives(sf::RenderWindow& window);
	void DrawLevel(sf::RenderWindow& window);
	void DrawTime(sf::RenderWindow& window);

	std::vector<std::shared_ptr <sf::Texture>> m_textures;

	int m_number_of_level;

	int lives;

	Player* m_player;
	Score * m_score;
	Clock * m_clock;

	int *m_time;
};