#include "EnemyController.h"
#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"

void EnemyController::init_controller()
{
	m_enemies = m_map->GetEnemies();
}
//-----------------------------------------------------------------------------

void EnemyController::move_enemies(float dt)
{
	int i = 0;

	while (i < m_enemies.size())
	{
		switch (m_enemies[i]->get_iq())
		{
		case IQ::Smart:
			m_enemies[i]->move(dt);
			break;

		case IQ::Random:
			m_enemies[i]->move(dt);
			break;

		case IQ::OneSide:

			m_enemies[i]->move(dt);
			break;
		}

		++i;
	}
}
//-----------------------------------------------------------------------------

bool EnemyController::reached_player(Map * map)
{
	sf::Vector2f player_loc = map->GetPlayer()->get_location();

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->get_sprite().getGlobalBounds().contains(player_loc))
			return true;
	}
	return false;
}
//-----------------------------------------------------------------------------

void EnemyController::set_paths()
{
	int i = 0;
	while (i < m_enemies.size())
	{
		switch (m_enemies[i]->get_iq())
		{
		case IQ::Smart:
			if (m_enemies[i]->path_is_empty())
				m_enemies[i]->set_path(Astar::calc_path(m_map, *this, m_enemies[i]->get_location()));
			break;

		case IQ::Random:
			if (m_enemies[i]->path_is_empty())
				m_enemies[i]->set_path(RandomPath::calc_path(m_map, *this, m_enemies[i]->get_location()));
			break;

		case IQ::OneSide:
			if (m_enemies[i]->path_is_empty())
				m_enemies[i]->set_path(OneSide::calc_path(m_map, *this, m_enemies[i]->get_location()));
			break;

		}
		++i;
	}
}
//-----------------------------------------------------------------------------