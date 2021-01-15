#include "Player.h"
#include "RigidBodyObject.h"
#include "StaticObject.h"
#include "Coin.h"
#include "Present.h"
#include "Ladder.h"
#include "Pole.h"
#include "Map.h"

void Player::Move(sf::Keyboard::Key key,float dt)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		update_location(NextStep::LEFT,dt);
		break;
	case sf::Keyboard::Right:
		update_location(NextStep::RIGHT,dt);
		break;
	case sf::Keyboard::Up:
		update_location(NextStep::UP,dt);
		break;
	case sf::Keyboard::Down:
		update_location(NextStep::DOWN,dt);
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Object& object)
{
	if (this->get_name() == object.get_name()) return;
	this->handle_collision(object);
}
void Player::handle_collision(StaticObject& object)
{
	object.handle_collision(*this);
}

void Player::handle_collision(Player& object)
{
}
void Player::handle_collision(Enemy& object)
{
}
void Player::handle_collision(Coin& object)
{
	m_map->DeleteCoin(object);
}
void Player::handle_collision(Present& object)
{
	m_map->DeletePresent(object);
}

void Player::handle_collision(Pole& object)
{
	on_pole(object.get_location());
}

void Player::handle_collision(Ladder& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.width >= 20)
			m_gravity = false;
}

void Player::handle_collision(RigidBodyObject& object)
{
	sf::FloatRect inter;
	if(get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(),inter))
	if(inter.height >=1 && inter.width >= 1)
	move_back();
}

void Player::set_map(Map* map)
{
	m_map = map;
}