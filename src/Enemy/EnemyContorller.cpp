#include "EnemyController.h"
#include <iostream>
#include "OneSide.h"


EnemyController::EnemyController(Map & map)
{
	//
	//
	//
	//insert Algorithms
	//how many iteriations should pass untill we calc path again
	m_loop_counter = 35;
	m_curr_counter = 35;
	m_enemies = map.get_enemies();
}


void EnemyController::move_enemies(Map * map)
{
	int i = 0;

	/*
	if (enemy_reached_player)
	{

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
