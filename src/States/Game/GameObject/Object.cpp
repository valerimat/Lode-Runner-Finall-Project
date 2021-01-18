#include "Object.h"
#include <iostream>


Object::Object(char m_name,sf::Vector2f location):
	m_name(m_name)
{
	sf::Vector2f location_of_sprite;
	location_of_sprite.x = location.y * OFFSET;
	location_of_sprite.y = location.x * OFFSET + 50;
	m_sprite.setPosition(location_of_sprite);
};
//-----------------------------------------------------------------------------

char Object::get_name()
{
	return m_name;
}
//-----------------------------------------------------------------------------

sf::Vector2f Object::get_location()
{
	return m_sprite.getPosition();
}
//----------------------------------------------------------------------------

void Object::set_name(char &name)
{
	m_name = name;
}

//-----------------------------------------------------------------------------

sf::Sprite& Object::get_sprite()
{
	return m_sprite;
}