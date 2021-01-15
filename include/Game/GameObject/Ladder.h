#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"

class Ladder : public StaticObject
{
	using StaticObject::StaticObject;

	void handle_collision(Player& player)
	{
		player.handle_collision(*this);
	}
	void handle_collision(Enemy& ene)
	{
		ene.handle_collision(*this);
	}
};