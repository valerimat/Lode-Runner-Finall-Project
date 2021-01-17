#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Player.h"
#include "Enemy.h"

class RigidBodyObject : public StaticObject
{
	using StaticObject::StaticObject;
	bool make_hole() override
	{
		//need something more generic
		if (get_location().x != 0 && get_location().x != SIZE_OF_TILE * 20)
		{
			m_hole = true;

			m_sprite.setPosition(get_location() + sf::Vector2f(0, SIZE_OF_TILE*0.875));

			m_sprite.setScale(0.8, 0.1);
			//m_sprite.setColor(sf::Color(0, 0, 0, 0));
			return true;
		}
		return false;
	}
	void handle_collision(DynamicObject& object)
	{
		object.handle_collision(*this);
	
	}
	void handle_collision(Player & object)
	{
		object.handle_collision(*this);

	}
	void handle_collision(Enemy& object)
	{
		object.handle_collision(*this);

	}

};