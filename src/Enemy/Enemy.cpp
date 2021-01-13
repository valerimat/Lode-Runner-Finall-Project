#include "Enemy.h"
#include "RigidBodyObject.h"
#include "StaticObject.h"
#include "Coin.h"
#include "Present.h"
#include "Pole.h"
#include "Map.h"
#include "OneSide.h"
#include "Algo.h"
#include "RandomPath.h"

//Ctors
Enemy::Enemy(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture, int smart) :
	DynamicObject(name, locaiton, texture)
{
	set_smartness(smart);
	switch (m_iq)
	{
	case IQ::Smart:
		algo = new RandomPath;
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

//Getter:
IQ Enemy::get_iq()
{
	return m_iq;
}
//-----------------------------------------------------------------------------
void Enemy::set_map(Map* map)
{
	m_map = map;
}
//Setter:
void Enemy::set_waypoint()
{
	if (waypoints.size() == 0)
	{
		sf::FloatRect rect = m_sprite.getGlobalBounds();
		Graph g = m_map->get_graph();
		waypoints = algo->calc_path(g, rect);
		next_waypoint = waypoints[0];
		waypoints.erase(waypoints.begin());
	}
	else
	{
		next_waypoint = waypoints[0];
		waypoints.erase(waypoints.begin());
	}
}
bool Enemy::checke_if_reached()
{
	sf::Vector2f our_loc = m_sprite.getPosition();

	if (abs(our_loc.x - next_waypoint.x) < 1 && abs(our_loc.y - next_waypoint.y) < 1)
	{
		return true;
	}
}
//-----------------------------------------------------------------------------
void Enemy::set_smartness(int i)
{
	m_iq = IQ(i);
}
//-----------------------------------------------------------------------------

void Enemy::move(float dt)
{
	NextStep step = direction_to_waypoint();
	switch (step)
	{
	case NextStep::LEFT:
		update_location(NextStep::LEFT,dt);
		break;
	case NextStep::RIGHT:
		update_location(NextStep::RIGHT,dt);
		break;
	case NextStep::UP:
		update_location(NextStep::UP,dt);
		break;
	case NextStep::DOWN:
		update_location(NextStep::DOWN,dt);
		break;
	case NextStep::NONE:
		set_waypoint();
		break;
	default:
		break;
	}
	if (checke_if_reached())
	{
		set_waypoint();
	}
}
//-----------------------------------------------------------------------------
NextStep Enemy::direction_to_waypoint()
{
	sf::Vector2f location = m_sprite.getPosition() + sf::Vector2f(20, 20); //for center
	if(next_waypoint == sf::Vector2f(-1,-1))
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

bool Enemy::no_waypoints()
{
	if (waypoints.size() == 0)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Enemy::handle_collision(Enemy& object) {};
void Enemy::handle_collision(Coin& object) {};
void Enemy::handle_collision(Present& object) {};

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
	m_gravity = false;
}

void Enemy::handle_collision(RigidBodyObject& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.height >= 1 && inter.width >= 1)
			move_back();
	//reset_path();
}

