#include "PlayerController.h"
#include "Player.h"
#include "Map.h"

PlayerController::PlayerController(Map& map)
{
	m_player = map.get_player();
}


void PlayerController::move_player(sf::Keyboard::Key key, Map& map)
{
	

	// later we add if statments
	std::vector<char> collision = m_player->is_on_something(map, key);
	

	for (int i = 0; i < collision.size(); i++)
	{
		std::cout << collision[i] << " ";
	}

	std::cout << std::endl;

	m_player->move(key);


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