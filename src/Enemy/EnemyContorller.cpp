#include "EnemyController.h"
#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"

//=============================================================================
void EnemyController::init_controller()
{
	m_enemies = m_map->get_enemies();
	set_curr_location();
	set_previous_location();
	for (auto enemy : m_enemies)
	{
		enemy->set_map(m_map);
		enemy->set_waypoints();
	}

}
//=============================================================================

//=============================================================================
void EnemyController::move(float dt)
{	
	sf::Vector2f before_g;
	sf::Vector2f after_g;

	if (m_enemies.size() != m_map->get_enemies().size())
	{
		init_controller();
	}

	for(int i =0;i < m_enemies.size(); ++i)
	{

		if (m_enemies[i]->check_reached())
		{
			
			m_enemies[i]->set_waypoints();
			continue;
		}

		//so we wont move
		if (!m_enemies[i]->is_in_hole())
		move_enemy(dt, *m_enemies[i]);

		before_g = m_enemies[i]->get_location();

		//sow we wont move
		if (!m_enemies[i]->is_in_hole())
		apply_gravity(dt, *m_enemies[i]);
		
		after_g = m_enemies[i]->get_location();

		//check if gravity works
		if (enemy_falling(before_g, after_g))
			m_enemies[i]->set_m_falling(true);
		else
			m_enemies[i]->set_m_falling(false);

		set_curr_location();

		check_stuck();
	}
}
//=============================================================================

//=============================================================================
void EnemyController::set_path()
{
	for (auto enemy : m_enemies)
	{
		if (enemy->check_reached())
			enemy->set_waypoints();
	}
}
//=============================================================================

//=============================================================================
void EnemyController::set_curr_location()
{
	curr_loc.clear();
	for (auto enemy : m_enemies)
	{
		curr_loc.push_back(enemy->get_location());
	}
}
//=============================================================================

//=============================================================================
void EnemyController::set_previous_location()
{
	prev_loc.clear();
	for (auto enemy : m_enemies)
	{
		prev_loc.push_back(enemy->get_location());
	}
}
//=============================================================================

//=============================================================================
void EnemyController::check_stuck()
{
	for (int i = 0; i < curr_loc.size(); ++i)
	{
		if (prev_loc[i] == curr_loc[i])
		{
			//m_enemies[i]->DontMove();
			m_enemies[i]->up_stuck();

			if (m_enemies[i]->stuck())
			{
				m_enemies[i]->reset_path();
				m_enemies[i]->set_waypoints();
			}
		}
		else
		{
			m_enemies[i]->reset_stuck();
		}
	}
}
//=============================================================================

//=============================================================================
void EnemyController::move_enemy(float dt, Enemy & enemy)
{
	set_previous_location();

	

	if (!enemy.get_m_falling())
	{
		enemy.move(dt);
	}

	//reset gravity bool
	enemy.turn_gravity_on();

	m_map->check_collision(enemy);
}
//=============================================================================

//=============================================================================
void EnemyController::apply_gravity(float dt, Enemy& enemy)
{
	//do graviry do its job
	enemy.gravity(dt);

	//check collisions again
	m_map->check_collision(enemy);
}
//=============================================================================

//=============================================================================
bool EnemyController::enemy_falling(sf::Vector2f before, sf::Vector2f after)
{
	if (abs(before.y -  after.y) > 0.f)
		return true;
	
	return false;
}
//=============================================================================