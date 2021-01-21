#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bonus.h"

class LivesBonus;
class TimeBonus;
class ScoreBonus;
class EnemyBonus;

class Present : public StaticObject
{
public:
	//using StaticObject::StaticObject;
	Present(char Name, sf::Vector2f locaiton, sf::Texture * texture);

	void handle_collision(DynamicObject& object);
	void handle_collision(Player& object);
	void handle_collision(Enemy& object);
	int get_type();
	Bonus* get_bonus();


private:
	int m_type;

	Bonus *m_bonus;
};