#pragma once
#include <SFML/Graphics.hpp>
#include "MovementController.h"

class Player;
class Map;

class PlayerController :public MovementController
{
public:
	PlayerController(Map &map);
	void move_player(sf::Keyboard::Key key, Map& map);

private:
	Player* m_player;
};