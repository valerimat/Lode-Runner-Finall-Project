#pragma once
#include "Map.h"
#include "MapData.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(MapData &map);
	void Draw(sf::RenderWindow &window);
	void Load_level();
	Map get_curr_map();

private:
	int level = 0;
	MapData m_maps;
	Map m_curr_map;
	Hud m_hud;
};