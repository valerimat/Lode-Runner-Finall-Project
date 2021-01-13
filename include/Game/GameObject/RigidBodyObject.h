#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"

class RigidBodyObject : public StaticObject
{
	using StaticObject::StaticObject;
	void handle_collision(Player& player)
	{
		player.handle_collision(*this);
	
	}
	void handle_collision(Enemy& enemy)
	{
		enemy.handle_collision(*this);
	}
};