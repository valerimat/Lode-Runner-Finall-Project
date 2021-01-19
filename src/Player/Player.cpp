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
Player::Player(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture) :
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
		if (inter.width > 5 && inter.height > 5)
		{
			m_lives.dec_lives();
			m_map->reset_positions();
		}
	std::cout << "collision";
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Coin& object)
{
	Score::GetScore().IncreasePoints(); // 1 represents the lvl needs to be changed latter
	m_map->DeleteCoin(object);
	m_music->EaitngSound();
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
	m_map->DeletePresent(object);
	m_music->DrinkingSound();
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Pole& object)
{
	on_pole(object.get_location());
	if (!m_standing)
		m_music->RopeSound();
}
//-----------------------------------------------------------------------------

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
//-----------------------------------------------------------------------------

void Player::handle_collision(RigidBodyObject& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.height >= 2 && inter.width >= 3)
		{
			move_back(object);
		}

	if(!m_standing)
		m_music->RunningSound();
}
//-----------------------------------------------------------------------------

void Player::SetMap(Map* map)
{
	m_map = map;
}
//-----------------------------------------------------------------------------

void Player::DeleteLeft()
{
	m_map->make_hole(get_location() + sf::Vector2f(-10, 45));
}
//-----------------------------------------------------------------------------

void Player::delete_right()
{
	m_map->make_hole(get_location() + sf::Vector2f(50, 45));
}
//-----------------------------------------------------------------------------

int Player::GetLives()
{
	return m_lives.GetLives();
}
//-----------------------------------------------------------------------------

void Player::AddLives()
{
	return m_lives.AddLives();
}
//-----------------------------------------------------------------------------