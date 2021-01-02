#pragma once
#include "Macros.h"
class Map;
#include <SFML/Graphics.hpp>


class VeryStupid
{
public:
	VeryStupid() = default;
	std::vector<NextStep> calc_path(Map map, sf::Vector2f curr_location);
	bool next_step_is_valid(Map map, NextStep next, sf::Vector2f curr_location_with_steps);
	void update_curr_location(sf::Vector2f & curr_location_with_steps, NextStep next);
};