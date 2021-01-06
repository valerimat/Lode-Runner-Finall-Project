#include "Object.h"
#include <iostream>
Object::Object()
{};

Object::Object(char m_name,sf::Vector2f location):
	m_name(m_name)
{
	m_location.x = location.y * OFFSET;
	m_location.y = location.x * OFFSET + 50;
};

char Object::get_name()
{
	return m_name;
}

sf::Vector2f Object::get_location()
{
	return m_location;
}

void Object::init_object(char m_name, sf::Vector2f  m_location)
{
	set_name(m_name);
	set_location(m_location);
}

void Object::set_name(char &name)
{
	m_name = name;
}

void Object::set_location(sf::Vector2f &location)
{
	m_location = location;
}
