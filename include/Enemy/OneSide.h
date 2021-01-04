#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

class Map;
class Enemy;

namespace OneSide
{
	std::vector<NextStep> calc_path(Map* map, Enemy& enemy);
	bool is_there_still_floor(NextStep next, Map* map, sf::Vector2f& curr_location_with_steps,float heihght);
	void update_curr_location(sf::Vector2f& curr_location_with_steps, NextStep next);
	bool is_dir_avaliable(NextStep next, std::vector<NextStep> avaliable);
	bool is_opposide_avaliable(NextStep next, std::vector<NextStep> avaliable);
}