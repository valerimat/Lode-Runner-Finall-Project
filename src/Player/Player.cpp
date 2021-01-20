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

// c-tor
Player::Player(char name, sf::Vector2f locaiton, sf::Texture * texture) :
	DynamicObject(name, locaiton, texture)
{
	on_create();
}
//-----------------------------------------------------------------------------

// init player
void Player::on_create()
{	
	m_base_location = get_location();
	m_lives.set_lives();
}
//-----------------------------------------------------------------------------

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

// double dispatch functions
void Player::handle_collision(Object& object)
{
	if (this->get_name() == object.get_name()) return;
	object.handle_collision(*this);
}
//-----------------------------------------------------------------------------

void Player::handle_collision(StaticObject& object)
{
	object.handle_collision(*this);
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Player& object)
{
	// empty
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Enemy& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.width >= 5 && inter.height >= 5)
		{
			if (object.is_in_hole())
			{
				if (inter.height >= 7)
				move_back(object);
			}
			else
			{
				m_map->reset_positions();
				std::cout << "collision";
				m_lives.dec_lives();
				Music::get_music().hurt_sound();
			}
		}
	
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Coin& object)
{
	Score::GetScore().increase_points(); // 1 represents the lvl needs to be changed latter
	m_map->delete_coin(object);
	Music::get_music().eating_sound();
}
//-----------------------------------------------------------------------------
void Player::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Present& object)
{
	std::cout << object.get_type() << std::endl;
	m_map->delete_present(object);
	Music::get_music().drinking_sound();
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Pole& object)
{
	on_pole(object.get_location());
	if (!m_standing)
		Music::get_music().rope_sound();
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Ladder& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.width >= 5)
    {
		m_gravity = false;
		if (!m_standing)
			Music::get_music().ladder_sound();
    }
}
//-----------------------------------------------------------------------------

void Player::handle_collision(RigidBodyObject& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.height >= 4 && inter.width >= 4)
		{
			move_back(object);
		}

	if(!m_standing)
		Music::get_music().running_sound();
}
//-----------------------------------------------------------------------------

void Player::set_map(Map* map)
{
	m_map = map;
}
//-----------------------------------------------------------------------------

void Player::delete_left()
{
	m_map->make_hole(get_location() + sf::Vector2f(-10, 45));
}
//-----------------------------------------------------------------------------

void Player::delete_right()
{
	m_map->make_hole(get_location() + sf::Vector2f(50, 45));
}
//-----------------------------------------------------------------------------

int Player::get_lives()
{
	return m_lives.get_lives();
}
//-----------------------------------------------------------------------------

void Player::add_lives()
{
	return m_lives.add_lives();
}
//-----------------------------------------------------------------------------