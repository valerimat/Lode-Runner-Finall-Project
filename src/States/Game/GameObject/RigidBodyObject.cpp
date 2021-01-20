#include "RigidBodyObject.h"


//==============================================================================
bool RigidBodyObject::make_hole() 
{
	//edges
	if (get_location().x != 0
		&&
		get_location().x != 800 - MacroSettings::get_settings().get_size_of_tile())
	{
		m_hole = true;

		m_sprite.setPosition(get_location() + 
			     sf::Vector2f(0, MacroSettings::get_settings().get_size_of_tile() * 0.875f));

		m_sprite.setScale(0.8, MacroSettings::get_settings().get_scale_height() / 8.f);
		
		return true;
	}
	return false;
}
//=============================================================================

//=============================================================================
void RigidBodyObject::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void RigidBodyObject::handle_collision(Player& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void RigidBodyObject::handle_collision(Enemy& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
bool RigidBodyObject::IsHole()
{
	return m_hole;
}
//=============================================================================

