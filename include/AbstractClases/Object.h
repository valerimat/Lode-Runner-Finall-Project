#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>


class Object
{
public:

	//C-tor
	Object(char m_name, sf::Vector2f m_location);

	//Dtor
	virtual ~Object() = default;

	//Getters:
	char		 get_name();
	sf::Vector2f get_location();

	//Setters:
	void set_name(char & name);
	void set_location(sf::Vector2f & location);

protected:

	sf::Vector2f m_location;
	char m_name;
};