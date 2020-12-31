#pragma once
#include "Hud.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
private:
	void draw(sf::RenderWindow &window);

public:
	Hud * m_hud;
	Map * m_map;
	Player * m_player;
	Enemy *enemy;
};