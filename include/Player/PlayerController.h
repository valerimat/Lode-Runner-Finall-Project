#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "MovementController.h"

class Player;
class Map;

class PlayerController :public MovementController
{
public:
	PlayerController(Map &map);
	void move_player(sf::Keyboard::Key key, Map& map);
	void physics_player(sf::Keyboard::Key key, Map& map, std::vector<char> &collision);

private:
	Player* m_player;
};