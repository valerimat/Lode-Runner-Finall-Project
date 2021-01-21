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
//=============================================================================
Player::Player(char name, sf::Vector2f locaiton, sf::Texture * texture) :
	DynamicObject(name, locaiton, texture)
{
	on_create();
}
//=============================================================================

// init player
//=============================================================================
void Player::on_create()
{	
	m_base_location = get_location();
	m_lives.set_lives();
}
//=============================================================================

//=============================================================================
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
//=============================================================================

// double dispatch functions
//=============================================================================
void Player::handle_collision(Object& object)
{
	if (this->get_name() == object.get_name()) return;
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Player::handle_collision(StaticObject& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Player::handle_collision(Player& object)
{
	// empty
}
//=============================================================================

//=============================================================================
void Player::handle_collision(Enemy& object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		{

			//so we walk on him
			if (object.is_in_hole())
			{
				if (inter.height >= m_size_of_tile / 10.f
					&&
					inter.width >= m_size_of_tile / 10.f)
				move_back(object);
			}
			else
			{

				if (inter.height >= m_size_of_tile / 7.f 
					&&
					inter.width >= m_size_of_tile / 7.f)
				{
					m_map->reset_positions();
					m_lives.dec_lives();
					Music::get_music().hurt_sound();
				}
			}
		}
	
}
//=============================================================================

//=============================================================================
void Player::handle_collision(Coin& object)
{
	Score::GetScore().increase_points(); // 1 represents the lvl needs to be changed latter
	m_map->delete_coin(object);
	Music::get_music().eating_sound();
}
//=============================================================================

//=============================================================================
void Player::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Player::handle_collision(Present& object)
{
	m_map->delete_present(object);
	Music::get_music().drinking_sound();
}
//=============================================================================

//=============================================================================
void Player::handle_collision(Pole& object)
{
	on_pole(object.get_location());

	if (!m_standing)
		Music::get_music().rope_sound();
}
//=============================================================================

//=============================================================================
void Player::handle_collision(Ladder& object)
{
	collide_with_ladder(object);

	if (!m_standing)
		Music::get_music().ladder_sound();
}
//=============================================================================

//=============================================================================
void Player::handle_collision(RigidBodyObject& object)
{
	collide_with_rigid_body(object);

	if(!m_standing)
		Music::get_music().running_sound();
}
//=============================================================================

//=============================================================================
void Player::set_map(Map* map)
{
	m_map = map;
}
//=============================================================================

//=============================================================================
void Player::delete_left()
{
	m_map->make_hole(BottomLeft());
}
//=============================================================================

//=============================================================================
void Player::delete_right()
{
	m_map->make_hole(BottomRight());
}
//=============================================================================

//=============================================================================
int Player::get_lives()
{
	return m_lives.get_lives();
}
//=============================================================================

//=============================================================================
void Player::add_lives()
{
	return m_lives.add_lives();
}
//=============================================================================

//=============================================================================
sf::Vector2f Player::BottomLeft()
{
	sf::Vector2f our_loc = get_location();
	float offset_y = MacroSettings::get_settings().get_size_of_tile() + 2;
	float offset_x = MacroSettings::get_settings().get_size_of_tile() / 2; // so we wont get our tile
	return our_loc + sf::Vector2f(-offset_x, offset_y);
}
//=============================================================================

//=============================================================================
sf::Vector2f Player::BottomRight()
{
	sf::Vector2f our_loc = get_location();
	float offset_y = MacroSettings::get_settings().get_size_of_tile() + 2;
	float offset_x = (MacroSettings::get_settings().get_size_of_tile() / 2)+
		             (MacroSettings::get_settings().get_size_of_tile()); // so we wont get our tile

	return our_loc + sf::Vector2f(offset_x, offset_y);
}
//=============================================================================