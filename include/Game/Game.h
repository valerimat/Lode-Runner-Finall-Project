#pragma once
#include "Map.h"
#include "MapData.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>
#include "Score.h"
class Game
{
public:
	Game(MapData &map);
	void Draw(sf::RenderWindow &window);
	void LoadLevel();
	Map * GetCurrMap();
	void InitHud();

private:
	int level = 0;
	Score m_score;
	MapData m_maps;
	Map m_curr_map;
	Hud  m_hud;
};