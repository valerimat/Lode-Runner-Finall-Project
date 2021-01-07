#pragma once
#include "Map.h"
#include "MapData.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>
#include "Score.h"
class Game
{
public:

	// c-tors
	Game(MapData &map);

	// getters
	Map* GetCurrMap();

	// Game functions
	void LoadLevel();
	void InitHud();
	void Draw(sf::RenderWindow& window);


private:

	//members
	int level = 0;
	Score m_score;
	MapData m_maps;
	Map m_curr_map;
	Hud  m_hud;
};