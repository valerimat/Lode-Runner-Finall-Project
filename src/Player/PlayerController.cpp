#include "PlayerController.h"
#include "Player.h"
#include "Map.h"

PlayerController::PlayerController(Map& map)
{
	m_player = map.get_player();
}


void PlayerController::move_player(sf::Keyboard::Key key, Map& map)
{
	std::vector<char> collision = m_player->is_on_something(map, key);

	for (int i = 0; i < collision.size(); i++)
	{
		std::cout << collision[i] << " ";
	}

	std::cout << std::endl;

	physics_player(key, map, collision);

	//m_player->move(key);

	//if (m_player->is_on_ground(map))
		//std::cout << "GROUND\n";
	//if (m_player->is_on_ladder(map))
		//std::cout << "LADDER\n";
	//if (m_player->is_on_pole(map))
	//	std::cout << "POLE\n";
	//if (m_player->is_on_wall(map))
	//	std::cout << "WALL\n";
	//if (m_player->is_on_air(map))
	//	std::cout << "AIR\n";
	//if (m_player->is_on_coin(map))
	//	std::cout << "COIN\n";
}

void PlayerController::physics_player(sf::Keyboard::Key key, Map& map, std::vector<char>& collision)
{
	bool ground = false, wall = false, ladder = false,
		 pole = false, coin = false, enemy = false;

	// lets us work will boolean values and be on track more easily
	for (int i = 0; i < collision.size(); i++)
	{
		if (collision[i] == GROUND)
			ground = true;
		if (collision[i] == WALL)
			wall = true;
		if (collision[i] == LADDER)
			ladder = true;
		if (collision[i] == POLE)
			pole = true;
		if (collision[i] == COIN)
			coin = true;
		if (collision[i] == ENEMY)
			enemy = true;
	}

	// free fall
	if (!ground && !ladder && !pole && key != sf::Keyboard::Up)
	{
		m_player->move(sf::Keyboard::Down);
		std::vector<char> collision = m_player->is_on_something(map, sf::Keyboard::Down);
		//std::this_thread::sleep_for(std::chrono::milliseconds(30));
		physics_player(key, map, collision);
	}

	// on ground
	if(ground && !wall && (key == sf::Keyboard::Left || key == sf::Keyboard::Right))
		m_player->move(key);

	// on ladder
	if (ladder && !wall)
	{
		if (ground && sf::Keyboard::Down)
			return;
		m_player->move(key);
		std::cout << "ladder\n";
	}

	// on pole
	if (pole && !wall && (key == sf::Keyboard::Left || key == sf::Keyboard::Right ||
		key == sf::Keyboard::Down))
		m_player->move(key);

	// wall = no movement forward
	if (wall)
	{
		std::cout << "wall\n";
		return;
	}
}
