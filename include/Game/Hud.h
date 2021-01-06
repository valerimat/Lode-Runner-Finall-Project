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
	void SetScore();
	void SetLives();
	void LoadTextures();
	void DrawScore(sf::RenderWindow& window);
	void DrawLives(sf::RenderWindow& window);
	void DrawLevel(sf::RenderWindow& window);
	void DrawTime(sf::RenderWindow& window);
private:
	std::vector<std::shared_ptr <sf::Texture>> m_textures;
	int m_number_of_level;
	Player* m_player;
	Score * m_score;
};