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
Enemy::Enemy(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture) :
	DynamicObject(name, locaiton, texture)
{
	on_create();
}
//-----------------------------------------------------------------------------

void Enemy::on_create()
{
	//
	m_base_location = get_location();

	//random number
	auto random = std::random_device();
	std::cout << random() << std::endl;
	auto smartness = rand() % 3;
	SetSmartness(smartness);

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
IQ Enemy::GetIQ()
{
	return m_iq;
}
//-----------------------------------------------------------------------------

sf::Vector2f Enemy::GetCenter()
{
	sf::Vector2f our_loc = get_location();

	sf::Vector2f center_offset(MacroSettings::GetSettings().GetScaleWidth()*50 / 2, MacroSettings::GetSettings().GetScaleWidth()*50 / 2);
	our_loc += center_offset;

	return our_loc;
}
//-----------------------------------------------------------------------------

//Setter:
//for movement:
void Enemy::SetWaypoint()
{
 	if (NoWaypoints())
	{
		ResetPath();
		SetNextWaypoint();
	}
	else
	{
		SetNextWaypoint();
	}
}
//-----------------------------------------------------------------------------

void Enemy::SetNextWaypoint()
{
	
	next_waypoint = waypoints[0];
	waypoints.erase(waypoints.begin());

}
//-----------------------------------------------------------------------------

void Enemy::ResetPath()
{
	waypoints.clear();
	waypoints = algo->CalcPath(m_map->get_graph(), get_location(), m_map->get_player()->get_location());
	
}
//-----------------------------------------------------------------------------

//for data:
void Enemy::SetMap(Map* map)
{
	m_map = map;
}
//-----------------------------------------------------------------------------

void Enemy::SetSmartness(int i)
{
	m_iq = IQ(i);
}
//-----------------------------------------------------------------------------

//for movement:
void Enemy::move(float dt)
{
	rect.setPosition(next_waypoint);
	rect.setSize(sf::Vector2f(40, 40));
	rect.setFillColor(sf::Color::Blue);
	//m_falling = false;
	//std::cout << next_waypoint.x << " " << next_waypoint.y << std::endl;
	NextStep step = DirectionToWaypoint();
	
	switch (step)
	{
	case NextStep::LEFT:
		update_location(NextStep::LEFT, dt);
		//std::cout << "left" << std::endl;
		break;
	case NextStep::RIGHT:
		update_location(NextStep::RIGHT, dt);
		//std::cout << "RIGHT" << std::endl;
		break;
	case NextStep::UP:
		update_location(NextStep::UP, dt);
		//std::cout << "up" << std::endl;
		break;
	case NextStep::DOWN:
		update_location(NextStep::DOWN, dt);
		//std::cout << "down" << std::endl;
		break;
	case NextStep::NONE:
		//std::cout << "none" << std::endl;
		//reset_path();
		//set_next_waypoint();
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------

//for unstucking:
void Enemy::UpStuck()
{
	stuck_counter++;
}
//-----------------------------------------------------------------------------

void Enemy::ResetStuck()
{
	stuck_counter = 0;
}
//-----------------------------------------------------------------------------

bool Enemy::Stuck()
{
	if (stuck_counter == 500)
	{
		//std::cout << stuck_counter;
		stuck_counter = 0;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------

bool Enemy::CheckIfReached()
{
	sf::Vector2 location = GetCenter();

	//if we reached the waypoint in 2 pixels diffrence
	if (abs(location.x - next_waypoint.x) < 3
		&&
		abs(location.y - next_waypoint.y) < 3)
	{
		//std::cout << "true";
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------

//For waypoints:
NextStep Enemy::DirectionToWaypoint()
{
	sf::Vector2f location = GetCenter();

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
//-----------------------------------------------------------------------------

bool Enemy::NoWaypoints()
{
	if (waypoints.size() == 0)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

void Enemy::DontMove()
{
	//waypoints.clear();
	//next_waypoint = sf::Vector2f(-1, -1);
}
//-----------------------------------------------------------------------------

//Collision:
//Ignored::
void Enemy::handle_collision(Enemy& object) {};
//-----------------------------------------------------------------------------
void Enemy::handle_collision(Coin& object) {};
//-----------------------------------------------------------------------------
void Enemy::handle_collision(Present& object) {};
//-----------------------------------------------------------------------------

//Not ignored:
void Enemy::handle_collision(Object & object)
{
	if (this->get_name() == object.get_name()) return;
	object.handle_collision(*this);
}
//-----------------------------------------------------------------------------
void Enemy::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
void Enemy::handle_collision(StaticObject& object)
{
	object.handle_collision(*this);
}
//-----------------------------------------------------------------------------

void Enemy::handle_collision(Player& object)
{
	object.handle_collision(*this);
}
//-----------------------------------------------------------------------------

void Enemy::handle_collision(Pole& object)
{
	on_pole(object.get_location());
}
//-----------------------------------------------------------------------------

void Enemy::handle_collision(Ladder& object) 
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.width >= 20)
			m_gravity = false;
}
//-----------------------------------------------------------------------------

void Enemy::handle_collision(RigidBodyObject& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.height >= 2 && inter.width >= 3)
		{
			move_back(object);
		}
	//reset_path();
}
//-----------------------------------------------------------------------------

