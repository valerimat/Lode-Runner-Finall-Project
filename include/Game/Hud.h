#pragma once
class Score;
class Player;
#include <SFML/Graphics.hpp>

class Hud
{
public:
	Hud();
	Hud(Score* score, Player* player, int num_of_level);
	void Draw(sf::RenderWindow& window);
	void set_score();
	void set_live();
	void load_textures();
	void Draw_score(sf::RenderWindow& window);
	void Draw_lives(sf::RenderWindow& window);
	void Draw_level(sf::RenderWindow& window);
	void Draw_time(sf::RenderWindow& window);
private:
	std::vector<std::shared_ptr <sf::Texture>> m_textures;
	int m_number_of_level;
	Player* m_player;
	Score * m_score;
};