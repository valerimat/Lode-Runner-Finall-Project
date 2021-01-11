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
	void init_controller();
	//PlayerController(Map &map);
	void MovePlayer( float dt);
	//void physics_player(sf::Keyboard::Key key, Map& map, std::vector<char> &collision);
	void set_paths();
	void check_key_press(sf::Keyboard::Key& pressed);

private:
	Player* m_player;
};