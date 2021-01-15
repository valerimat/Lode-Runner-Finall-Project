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

static int number = 0;
//Ctors
Enemy::Enemy(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture, int smart) :
	DynamicObject(name, locaiton, texture)
{
	m = number;
	number++;
	set_smartness(smart);
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
//-----------------------------------------------------------------------------

//Getter:
IQ Enemy::get_iq()
{
	return m_iq;
}
//-----------------------------------------------------------------------------
sf::Vector2f Enemy::get_center()
{
	sf::Vector2f our_loc = get_location();

	sf::Vector2f center_offset(SIZE_OF_TILE / 2, SIZE_OF_TILE / 2);
	our_loc = our_loc += center_offset;

	return our_loc;
}
//-----------------------------------------------------------------------------

//Setter:
//for movement:
void Enemy::set_waypoint()
{
	if (no_waypoints())
	{
		reset_path();
		set_next_waypoint();
	}
	else
	{
		set_next_waypoint();
	}
}
//-----------------------------------------------------------------------------
void Enemy::set_next_waypoint()
{
	next_waypoint = waypoints[0];
	waypoints.erase(waypoints.begin());
}
//-----------------------------------------------------------------------------
void Enemy::reset_path()
{
	waypoints.clear();
	waypoints = algo->calc_path(m_map->get_graph(), get_location(), m_map->GetPlayer()->get_location());
	set_next_waypoint();
}
//-----------------------------------------------------------------------------

//for data:
void Enemy::set_map(Map* map)
{
	m_map = map;
}
//-----------------------------------------------------------------------------
void Enemy::set_smartness(int i)
{
	m_iq = IQ(i);
}
//-----------------------------------------------------------------------------
//for movement:
void Enemy::move(float dt)
{
	//do we need it here?
	/*
	if (checke_if_reached())
	{
		set_waypoint();
		return;
	}

	*/

	NextStep step = direction_to_waypoint();
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
		waypoints.clear();
		set_waypoint();
		break;
	default:
		break;
	}

}
//-----------------------------------------------------------------------------
//for unstucking:
void Enemy::up_stuck()
{
	stuck_counter++;
}

void Enemy::reset_stuck()
{
	stuck_counter = 0;
}
//-----------------------------------------------------------------------------
bool Enemy::stuck()
{
	if (stuck_counter == 10)
	{
		stuck_counter = 0;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
bool Enemy::checke_if_reached()
{
	sf::Vector2 location = get_center();

	//if we reached the waypoint in 2 pixels diffrence
	if (abs((location.x - next_waypoint.x) < 2
		&&
		abs(location.y - next_waypoint.y) < 2))
	{
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------
//For waypoints:
NextStep Enemy::direction_to_waypoint()
{
	sf::Vector2f location = get_center();

	//for safety
	if(next_waypoint == sf::Vector2f(-1,-1))
		return NextStep::NONE;

	if (abs(location.x - next_waypoint.x) > 2)
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
	else if (abs(location.y - next_waypoint.y) > 2)
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
//-----------------------------------------------------------------------------
bool Enemy::no_waypoints()
{
	if (waypoints.size() == 0)
		return true;

	return false;
}
//-----------------------------------------------------------------------------


//Collision:
//Ignored::
void Enemy::handle_collision(Enemy& object) {};
void Enemy::handle_collision(Coin& object) {};
void Enemy::handle_collision(Present& object) {};


//Not ignored:
void Enemy::handle_collision(Object & object)
{
	if (this->get_name() == object.get_name()) return;
	this->handle_collision(object);
}

void Enemy::handle_collision(StaticObject& object)
{
	object.handle_collision(*this);
}

void Enemy::handle_collision(Player& object)
{

}

void Enemy::handle_collision(Pole& object)
{
	on_pole(object.get_location());
}

void Enemy::handle_collision(Ladder& object) 
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.width >= 20)
			m_gravity = false;
}

void Enemy::handle_collision(RigidBodyObject& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.height >= 2 && inter.width >= 2)
			move_back();
	//reset_path();
}

