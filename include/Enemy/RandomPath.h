#pragma once
#include <vector>
#include "Macros.h"
#include <SFML/Graphics.hpp>
class EnemyController;
class Map;
class Enemy;

/*
Algorithm to generate random path
*/
namespace RandomPath
{
	//main call function:
	std::vector<NextStep> calc_path(Map* map, EnemyController& contorller, sf::Vector2f location);

	void update_curr_location(sf::Vector2f& curr_location_with_steps, NextStep next);
	bool is_dir_avaliable(NextStep next, std::vector<NextStep> avaliable);
};



