#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>


class Object
{
public:

	virtual ~Object() = default;

	Object();
	Object(char m_name, sf::Vector2f m_location);
	virtual void init_object(char  m_name, sf::Vector2f   m_location);


	char get_name();
	sf::Vector2f get_location();
	sf::Vector2f get_location_x_y();

	void set_name(char & name);
	void set_location(sf::Vector2f & location);

protected:
	sf::Vector2f m_location;
	char m_name;

};