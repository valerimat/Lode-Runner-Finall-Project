#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Player.h"
#include "Enemy.h"
#include "MacroSettings.h"

class RigidBodyObject : public StaticObject
{
public:
	using StaticObject::StaticObject;
	bool make_hole() override;
	bool IsHole();
	void RestOriginal();
	void SetHole(bool boolean);
	void handle_collision(DynamicObject& object);
	void handle_collision(Player& object);
	void handle_collision(Enemy& object);
private:
	sf::Vector2f origina_pos;
};