#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Enemy.h"
#include "Player.h"

class Coin : public StaticObject
{
	using StaticObject::StaticObject;
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
};