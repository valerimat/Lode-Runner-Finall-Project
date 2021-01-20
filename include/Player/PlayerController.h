#pragma once
#include <SFML/Graphics.hpp>
#include "MovementController.h"
#include "Music.h"
#include "Player.h"
class Map;

class PlayerController : public MovementController
{
public:

	//
	using MovementController::MovementController;
	//
	void init_controller();
	//PlayerController(Map &map);
	void move_player( float dt);
	//void physics_player(sf::Keyboard::Key key, Map& map, std::vector<char> &collision)
	void check_key_press(sf::Keyboard::Key& pressed);

private:
	bool m_falling = false;
	Player * m_player;
};