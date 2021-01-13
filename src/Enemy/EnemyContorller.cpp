#include "EnemyController.h"
#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"

void EnemyController::init_controller()
{
	m_enemies = m_map->GetEnemies();
	for (auto enemy : m_enemies)
		enemy->set_map(m_map);
}
//-----------------------------------------------------------------------------

void EnemyController::move_enemies(float dt)
{	
	for (auto enemy : m_enemies)
	{
		if (!enemy->m_falling)
		{
			enemy->move(dt);
		}

		//reset gravity bool
		enemy->turn_gravity_on();

		m_map->check_collision(*enemy);

		sf::Vector2f before_g = enemy->get_location();

		//do graviry do its job
		enemy->gravity(dt);

		//check collisions again
		m_map->check_collision(*enemy);

		sf::Vector2f after_g = enemy->get_location();

		//we are falling if we were able to go down
		if (before_g != after_g)
			enemy->m_falling = true;
		else
			enemy->m_falling = false;
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
	for (auto enemy : m_enemies)
	{
		if (enemy->checke_if_reached())
			enemy->set_waypoint();
	}
}
//-----------------------------------------------------------------------------