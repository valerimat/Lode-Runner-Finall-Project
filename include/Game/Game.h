#pragma once
#include "Map.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(Map &map);
	void Draw(sf::RenderWindow &window);

private:
	Map m_map;
	Hud m_hud;
};