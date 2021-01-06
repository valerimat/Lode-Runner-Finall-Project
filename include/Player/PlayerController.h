#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "MovementController.h"
class Player;
class Map;

class PlayerController
	: public MovementController
{
public:

	//
	using MovementController::MovementController;
	//
	void init_player();
	//PlayerController(Map &map);
	void move_player(sf::Keyboard::Key key, float dt);
	//void physics_player(sf::Keyboard::Key key, Map& map, std::vector<char> &collision);
	void set_paths();

private:
	Player* m_player;
};