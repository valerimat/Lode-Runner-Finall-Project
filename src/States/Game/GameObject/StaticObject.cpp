#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Present.h"
#include "MacroSettings.h"

//==============================================================================
StaticObject::StaticObject(char name, sf::Vector2f locaiton, sf::Texture *texture):
Object(name,locaiton)
{
	set_sprite(texture);
}
//==============================================================================

//==============================================================================
void StaticObject::set_sprite(sf::Texture * texture)
{
	m_sprite.setTexture(*texture);
	m_sprite.setScale(sf::Vector2f(MacroSettings::get_settings().get_scale_width(), MacroSettings::get_settings().get_scale_height()));
}
//==============================================================================

//==============================================================================
void StaticObject::Draw(sf::RenderWindow & main_window)
{
	main_window.draw(m_sprite);
}
//==============================================================================

//==============================================================================
bool StaticObject::in_bounds(sf::Vector2f &location)
{
	if (m_sprite.getGlobalBounds().contains(location))
	{	
		return true;
	}	
	return false;
}
//==============================================================================

bool StaticObject::in_bounds(sf::RectangleShape& rect)
{
	if (m_sprite.getGlobalBounds().intersects(rect.getGlobalBounds()))
		return true;
	return false;
}
//==============================================================================


//===================== Collision
//==============================================================================
//ingored:
void StaticObject::handle_collision(RigidBodyObject& object) {};
void StaticObject::handle_collision(Player& object) {};
void StaticObject::handle_collision(StaticObject& object) {};
void StaticObject::handle_collision(Coin& object) {};
void StaticObject::handle_collision(Present& object) {};
void StaticObject::handle_collision(Ladder& object) {};
void StaticObject::handle_collision(Pole& object) {};

//==============================================================================
void StaticObject::handle_collision(Object& object)
{
	object.handle_collision(*this);
}
//==============================================================================

//==============================================================================
void StaticObject::handle_collision(Enemy& object)
{
	object.handle_collision(*this);
}
//==============================================================================

//==============================================================================
void StaticObject::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
//==============================================================================

//==============================================================================
bool StaticObject::get_hole()
{
	return m_hole;
}
//==============================================================================

//==============================================================================
void StaticObject::SetHole(bool boolean)
{
	m_hole = boolean;
}
//==============================================================================