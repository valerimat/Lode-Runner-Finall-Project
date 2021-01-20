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
	bool make_hole() override;

	void handle_collision(DynamicObject& object);
	void handle_collision(Player& object);
	void handle_collision(Enemy& object);

};