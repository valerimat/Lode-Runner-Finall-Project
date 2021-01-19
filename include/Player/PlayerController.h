#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "MovementController.h"
#include "Music.h"

class Player;
class Map;

class PlayerController
	: public MovementController
{
public:

	//
	using MovementController::MovementController;
	//
	void InitController();
	//PlayerController(Map &map);
	void MovePlayer( float dt);
	//void physics_player(sf::Keyboard::Key key, Map& map, std::vector<char> &collision)
	void check_key_press(sf::Keyboard::Key& pressed);

private:
	bool m_falling = false;
	Music* m_music = new Music;
	Player* m_player;
};