#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>


class Object
{
public:
	Object(char m_name, sf::Vector2f m_location);
	char get_name();
	sf::Vector2f get_location();

protected:
	sf::Vector2f m_location;
	char m_name;

};