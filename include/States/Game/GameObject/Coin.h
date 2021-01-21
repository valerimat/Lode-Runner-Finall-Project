#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Enemy.h"
#include "Player.h"

class Coin : public StaticObject
{
public:
	// c-tor
	using StaticObject::StaticObject;

	// handle collision
	void handle_collision(DynamicObject& object);
	void handle_collision(Player& object);
	void handle_collision(Enemy& object);
};