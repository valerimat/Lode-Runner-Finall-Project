#include "Player.h"
#include "RigidBodyObject.h"
#include "StaticObject.h"
#include "Coin.h"
#include "Score.h"
#include "Present.h"
#include "Ladder.h"
#include "Pole.h"
#include "Map.h"
#include "Music.h"

void Player::Move(sf::Keyboard::Key key,float dt)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		m_standing = false;
		update_location(NextStep::LEFT,dt);
		break;
	case sf::Keyboard::Right:
		m_standing = false;
		update_location(NextStep::RIGHT,dt);
		break;
	case sf::Keyboard::Up:
		m_standing = false;
		update_location(NextStep::UP,dt);
		break;
	case sf::Keyboard::Down:
		m_standing = false;
		update_location(NextStep::DOWN,dt);
		break;
	default:
		m_standing = true;
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
	Score::GetScore().IncreasePoints(1); // 1 represents the lvl needs to be changed latter
	m_map->DeleteCoin(object);
	m_music->EaitngSound();
}
void Player::handle_collision(Present& object)
{
	m_map->DeletePresent(object);
	m_music->DrinkingSound();
}

void Player::handle_collision(Pole& object)
{
	on_pole(object.get_location());
	if (!m_standing)
		m_music->RopeSound();
}

void Player::handle_collision(Ladder& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.width >= 20)
    {
		m_gravity = false;
		if (!m_standing)
		m_music->LadderSound();
    }
}

void Player::handle_collision(RigidBodyObject& object)
{
	sf::FloatRect inter;
	if(get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(),inter))
	if(inter.height >=1 && inter.width >= 1)
	move_back();
	if(!m_standing)
		m_music->RunningSound();
}

void Player::set_map(Map* map)
{
	m_map = map;
}