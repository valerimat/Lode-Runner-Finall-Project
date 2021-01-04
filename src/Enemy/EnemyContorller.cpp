#include "EnemyController.h"
#include <iostream>
#include "OneSide.h"


EnemyController::EnemyController(Map & map)
{
	m_enemies = map.get_enemies();
}


void EnemyController::move_enemies(Map * map)
{
	int i = 0;

	/*
	if (reached_player(map))
	{
		std::cout << "got to player" << std::endl;
	}
	*/

	while (i < m_enemies.size())
	{
		switch (m_enemies[i]->get_iq())
		{
		case IQ::Smart:
			 if(m_enemies[i]->path_is_empty())
				m_enemies[i]->set_path(Astar::calc_path(map, m_enemies[i]));
			else
				m_enemies[i]->move();
			break;

		case IQ::Random:
			if (m_enemies[i]->path_is_empty())
				m_enemies[i]->set_path(Astar::calc_path(map, m_enemies[i]));
			else
				m_enemies[i]->move();

			break;
		case IQ::OneSide:
			if (m_enemies[i]->path_is_empty())
			{
				m_enemies[i]->set_path(Astar::calc_path(map, m_enemies[i]));
				m_enemies[i]->move();
			}
			else
				m_enemies[i]->move();

			break;
		}

		++i;
	}
}

bool EnemyController::reached_player(Map * map)
{
	sf::Vector2f player_loc = map->get_player()->get_location();

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->get_sprite().getGlobalBounds().contains(player_loc))
			return true;
	}
	return false;
}