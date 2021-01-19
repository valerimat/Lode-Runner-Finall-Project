#include "EnemyController.h"
#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"
static int stuck = 0;

void EnemyController::InitController()
{
	m_enemies = m_map->GetEnemies();
	SetCurrLocation();
	SetPreviousLocations();
	for (auto enemy : m_enemies)
	{
		enemy->SetMap(m_map);
		enemy->set_waypoint();
	}
}
//-----------------------------------------------------------------------------

void EnemyController::MoveEnemies(float dt)
{	
	sf::Vector2f before_g;
	sf::Vector2f after_g;

	if (m_enemies.size() != m_map->GetEnemies().size())
	{
		InitController();
	}

	for(int i =0;i < m_enemies.size(); ++i)
	{

		if (m_enemies[i]->checke_if_reached())
		{
			
			m_enemies[i]->set_waypoint();
			continue;
		}

		MoveEnemy(dt, m_enemies[i]);

		before_g = m_enemies[i]->get_location();

		ApplyGravity(dt, m_enemies[i]);
		
		after_g = m_enemies[i]->get_location();

		if (EnemyFalling(before_g, after_g))
			m_enemies[i]->m_falling = true;
		else
			m_enemies[i]->m_falling = false;

		SetCurrLocation();

		CheckStuck();
	}
}
//-----------------------------------------------------------------------------

void EnemyController::SetPaths()
{
	for (auto enemy : m_enemies)
	{
		if (enemy->checke_if_reached())
			enemy->set_waypoint();
	}
}
//-----------------------------------------------------------------------------

void EnemyController::SetCurrLocation()
{
	curr_loc.clear();
	for (auto enemy : m_enemies)
	{
		curr_loc.push_back(enemy->get_location());
	}
}
//-----------------------------------------------------------------------------

void EnemyController::SetPreviousLocations()
{
	prev_loc.clear();
	for (auto enemy : m_enemies)
	{
		prev_loc.push_back(enemy->get_location());
	}
}
//-----------------------------------------------------------------------------

void EnemyController::CheckStuck()
{
	for (int i = 0; i < curr_loc.size(); ++i)
	{
		if (prev_loc[i] == curr_loc[i])
		{
			m_enemies[i]->dont_move();
			m_enemies[i]->up_stuck();

			if (m_enemies[i]->stuck())
			{
				m_enemies[i]->reset_path();
				m_enemies[i]->set_waypoint();
			}
		}
		else
		{
			m_enemies[i]->reset_stuck();
		}
	}
}
//-----------------------------------------------------------------------------

void EnemyController::MoveEnemy(float dt, Enemy * enemy)
{
	SetPreviousLocations();

	

	if (!enemy->m_falling)
	{
		enemy->move(dt);
	}

	//reset gravity bool
	enemy->turn_gravity_on();

	m_map->check_collision(*enemy);
}
//-----------------------------------------------------------------------------

void EnemyController::ApplyGravity(float dt, Enemy* enemy)
{
	//do graviry do its job
	enemy->gravity(dt);

	//check collisions again
	m_map->check_collision(*enemy);
}
//-----------------------------------------------------------------------------

bool EnemyController::EnemyFalling(sf::Vector2f before, sf::Vector2f after)
{
	if (abs(before.y -  after.y) > 0.f)
		return true;
	
	return false;
}
//-----------------------------------------------------------------------------