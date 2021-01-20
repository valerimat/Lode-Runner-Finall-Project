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
#include "MacroSettings.h"	

//Ctor:
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
	m_lives.SetLives();
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
		{
			//so we walk on him
			if (object.IsInHole())
			{
				if (inter.height >= 4 && inter.width >= 4)
				move_back(object);
			}
			else
			{
				if (inter.width >= 8 && inter.height >= 8)
				{
					m_map->reset_positions();
					m_lives.DecLives();
					Music::GetMusic().HurtSound();
				}
			}
		}
	
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Coin& object)
{
	Score::GetScore().IncreasePoints(); // 1 represents the lvl needs to be changed latter
	m_map->DeleteCoin(object);
	Music::GetMusic().EaitngSound();
}
//-----------------------------------------------------------------------------
void Player::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Present& object)
{
	m_map->DeletePresent(object);
	Music::GetMusic().DrinkingSound();
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Pole& object)
{
	on_pole(object.get_location());
	if (!m_standing)
		Music::GetMusic().RopeSound();
}
//-----------------------------------------------------------------------------

void Player::handle_collision(Ladder& object)
{
	CollideWithLadder(object);

	if (!m_standing)
		Music::GetMusic().LadderSound();
   
}
//-----------------------------------------------------------------------------

void Player::handle_collision(RigidBodyObject& object)
{
	CollideWithRigidBody(object);

	if(!m_standing)
		Music::GetMusic().RunningSound();
}
//-----------------------------------------------------------------------------

void Player::SetMap(Map* map)
{
	m_map = map;
}
//-----------------------------------------------------------------------------

void Player::DeleteLeft()
{
	m_map->make_hole(BottomLeft());
}
//-----------------------------------------------------------------------------

void Player::DeleteRight()
{
	m_map->make_hole(BottomRight());
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

sf::Vector2f Player::BottomLeft()
{
	sf::Vector2f our_loc = get_location();
	float offset_y = MacroSettings::GetSettings().GetSizeOfTile() + 2;
	float offset_x = MacroSettings::GetSettings().GetSizeOfTile() / 2; // so we wont get our tile
	return our_loc + sf::Vector2f(-offset_x, offset_y);
}

sf::Vector2f Player::BottomRight()
{
	sf::Vector2f our_loc = get_location();
	float offset_y = MacroSettings::GetSettings().GetSizeOfTile() + 2;
	float offset_x = (MacroSettings::GetSettings().GetSizeOfTile() / 2)+
		             (MacroSettings::GetSettings().GetSizeOfTile()); // so we wont get our tile

	return our_loc + sf::Vector2f(offset_x, offset_y);
}