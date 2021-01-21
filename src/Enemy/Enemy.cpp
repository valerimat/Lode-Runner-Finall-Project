#include "Enemy.h"
#include "RigidBodyObject.h"
#include "StaticObject.h"
#include "Coin.h"
#include "Present.h"
#include "Pole.h"
#include "Map.h"
#include "Ladder.h"
#include "OneSide.h"
#include "Algo.h"
#include "RandomPath.h"
#include "Bfs.h"
#include <random>

//Ctors
//=============================================================================
Enemy::Enemy(char name, sf::Vector2f locaiton, sf::Texture* texture) :
	DynamicObject(name, locaiton, texture)
{
	on_create();
}
//=============================================================================

//=============================================================================
void Enemy::on_create()
{
	//
	m_base_location = get_location();

	//random number
	auto random = std::random_device();

	auto smartness = rand() % 3;

	set_smartness(smartness);


	switch (m_iq)
	{
	case IQ::Smart:
		algo = new Bfs;
		break;
	case IQ::Random:
		algo = new RandomPath;
		break;
	case IQ::OneSide:
		algo = new OneSide;
		break;
	default:
		break;
	}
}
//=============================================================================

//Getter:
//=============================================================================
IQ Enemy::get_IQ()
{
	return m_iq;
}
//=============================================================================

//=============================================================================
sf::Vector2f Enemy::get_center()
{
	sf::Vector2f our_loc = get_location();

	sf::Vector2f center_offset(
		m_size_of_tile / 2.f,
		m_size_of_tile / 2.f);

	our_loc += center_offset;

	return our_loc;
}
//=============================================================================

//Setter:
//for movement:
//=============================================================================
void Enemy::set_waypoints()
{
	//if there are no waypoints
 	if (no_waypoints())
	{
		reset_path();
		set_next_waypoints();
	}
	else
	{
		set_next_waypoints();
	}
}
//=============================================================================

//=============================================================================
void Enemy::set_next_waypoints()
{
	
	next_waypoint = waypoints[0];
	waypoints.erase(waypoints.begin());

}
//=============================================================================

//=============================================================================
void Enemy::reset_path()
{
	waypoints.clear();
	waypoints = algo->calc_path(m_map->get_graph(), get_location(), m_map->get_player()->get_location());
}
//=============================================================================

//for data:
//=============================================================================
void Enemy::set_map(Map* map)
{
	m_map = map;
}
//=============================================================================

//=============================================================================
void Enemy::set_smartness(int i)
{
	m_iq = IQ(i);
}
//=============================================================================

//for movement:
//=============================================================================
void Enemy::move(float dt)
{

	NextStep step = DirectionToWaypoint();
	
	switch (step)
	{
	case NextStep::LEFT:
		update_location(NextStep::LEFT, dt);
		break;
	case NextStep::RIGHT:
		update_location(NextStep::RIGHT, dt);
		break;
	case NextStep::UP:
		update_location(NextStep::UP, dt);
		break;
	case NextStep::DOWN:
		update_location(NextStep::DOWN, dt);
		break;
	case NextStep::NONE:
		break;
	default:
		break;
	}
}
//=============================================================================

//for unstucking:
//=============================================================================
void Enemy::up_stuck()
{
	stuck_counter++;
}
//=============================================================================

//=============================================================================
void Enemy::reset_stuck()
{
	stuck_counter = 0;
}
//=============================================================================

//=============================================================================
bool Enemy::stuck()
{
	if (stuck_counter == 500)
	{
		stuck_counter = 0;
		return true;
	}
	return false;
}
//=============================================================================

//=============================================================================
bool Enemy::check_reached()
{
	sf::Vector2 location = get_center();

	//if we reached the waypoint in 2 pixels diffrence
	if (abs(location.x - next_waypoint.x) < m_size_of_tile/ 10.f
		&&
		abs(location.y - next_waypoint.y) < m_size_of_tile/ 10.f)
	{
		return true;
	}

	return false;
}
//=============================================================================

//Calculates which direction to move to reach waypoint
//=============================================================================
NextStep Enemy::DirectionToWaypoint()

{
	sf::Vector2f location = get_center();

	//for safety
	if(abs(next_waypoint.x - get_location().x) <1 && abs(next_waypoint.y - get_location().y) <1)
		return NextStep::NONE;

	if (abs(location.x - next_waypoint.x) > 1)
	{
		if (location.x - next_waypoint.x > 0)
		{
			return NextStep::LEFT;
		}
		else
		{
			return NextStep::RIGHT;
		}
	}
	else if (abs(location.y - next_waypoint.y) > 1)
	{
		if (location.y - next_waypoint.y > 0)
		{
			return NextStep::UP;
		}
		else
		{
			return NextStep::DOWN;
		}
	}

	return NextStep::NONE;
}
//=============================================================================

//=============================================================================
bool Enemy::no_waypoints()
{
	if (waypoints.size() == 0)
		return true;

	return false;
}
//=============================================================================

//Collision:
//Ignored::
//=============================================================================
void Enemy::handle_collision(Enemy& object) 
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
	{
		//so we walk on him
		if (object.is_in_hole())
		{
			if (inter.height >= m_size_of_tile / 10.f && inter.width >= m_size_of_tile / 10.f)
				move_back(object);

		}
	}
};
//=============================================================================

//=============================================================================
void Enemy::handle_collision(Coin& object) {};
//=============================================================================

//=============================================================================
void Enemy::handle_collision(Present& object) {};
//=============================================================================

//Not ignored:
//=============================================================================
void Enemy::handle_collision(Object & object)
{
	if (this->get_name() == object.get_name()) return;
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Enemy::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Enemy::handle_collision(StaticObject& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Enemy::handle_collision(Player& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Enemy::handle_collision(Pole& object)
{
	on_pole(object.get_location());
}
//=============================================================================

//=============================================================================
void Enemy::handle_collision(Ladder& object) 
{
	collide_with_ladder(object);
}
//=============================================================================

//=============================================================================
void Enemy::handle_collision(RigidBodyObject& object)
{
	collide_with_rigid_body(object);
}
//=============================================================================

//=============================================================================
void Enemy::reset_after_hole()
{
	reset_path();
	m_in_hole = false;
}

//-----------------------------------------------------------------------------
bool Enemy::get_m_falling()
{
	return m_falling;
}
//-----------------------------------------------------------------------------
void Enemy::set_m_falling(bool state)
{
	m_falling = state;
}
//-----------------------------------------------------------------------------

