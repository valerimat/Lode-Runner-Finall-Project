#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Player.h"
#include "Enemy.h"
#include "MacroSettings.h"

class RigidBodyObject : public StaticObject
{
	using StaticObject::StaticObject;
	bool make_hole() override
	{
		//need something more generic
		if (get_location().x != 0 && get_location().x != MacroSettings::GetSettings().GetScaleWidth() * 50 * 20)
		{
			m_hole = true;

			m_sprite.setPosition(get_location() + sf::Vector2f(0, MacroSettings::GetSettings().GetScaleWidth() * 50 * 0.875));

			m_sprite.setScale(0.8, MacroSettings::GetSettings().GetScaleHeight()/8);
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