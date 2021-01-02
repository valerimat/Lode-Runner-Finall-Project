#include "EnemyController.h"
#include <iostream>

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


void EnemyController::move_enemies(Map &map)
{
	int i = 0;
	bool recalc_path = false;
	VeryStupid verystupid;
	RandomPath rndpath;

	if (m_curr_counter == m_loop_counter)
		recalc_path = true;
	m_curr_counter++;
	while (i < m_enemies.size())
	{
		
		switch (m_enemies[i]->get_iq())
		{
		case IQ::Smart:
			if (recalc_path)
			{
				m_enemies[i]->set_path(verystupid.calc_path(map, m_enemies[i]->get_location()));
				m_enemies[i]->move();
				m_curr_counter = 0;
			}
			else
			{
				m_enemies[i]->move();
				
			}

		case IQ::Stupid:
			if (recalc_path)
			{
			
				m_enemies[i]->set_path(rndpath.calc_path(map, m_enemies[i]->get_location(), m_enemies[i]->get_width(), m_enemies[i]->get_height()));
				std::cout << m_enemies[i]->get_location().x << " " << m_enemies[i]->get_location().y << std::endl;
				m_enemies[i]->move();
				m_curr_counter = 0;
			}
			else
			{
				m_enemies[i]->move();
				
			}

			break;

		case IQ::VeryVeryStupid:
			if (recalc_path)
			{
				m_enemies[i]->set_path(verystupid.calc_path(map,m_enemies[i]->get_location()));
				m_enemies[i]->move();
				m_curr_counter = 0; 
			}
			else
			{
				m_enemies[i]->move();
			
			}

			break;
		default:
			break;
		}
		++i;
	}
}