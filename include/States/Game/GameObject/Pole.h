#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Player.h"
#include "Enemy.h"


class Pole : public StaticObject
{
	using StaticObject::StaticObject;

	void handle_collision(DynamicObject& object);
	void handle_collision(Player& object);
	void handle_collision(Enemy& object);
};