#include "Object.h"

Object::Object(char m_name,sf::Vector2f m_location):
	m_name(m_name), m_location(m_location)
{};

char Object::get_name()
{
	return m_name;
}

sf::Vector2f Object::get_location()
{
	sf::Vector2f location;
	location.x = m_location.x * OFFSET;
	location.y = m_location.y * OFFSET;
	return location;
}