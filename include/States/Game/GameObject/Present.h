#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Player.h"
#include "Enemy.h"

class Present : public StaticObject
{
public:
	//using StaticObject::StaticObject;
	Present(char Name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture)
		    :StaticObject(Name, locaiton, texture)
	{
		std::cout << "present was created with the type of ";
		m_type = rand() % 4;

		std::cout << m_type << std::endl;
	}

	void handle_collision(DynamicObject& object)
	{
		object.handle_collision(*this);
	}
	void handle_collision(Player& object)
	{
		object.handle_collision(*this);
	}
	void handle_collision(Enemy& object)
	{
		object.handle_collision(*this);
	}
	int get_type()
	{
		return m_type;
	}

private:
	int m_type;
};