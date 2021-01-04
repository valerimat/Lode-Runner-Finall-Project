#pragma once
#include <vector>
class Map;
class Enemy;
#include "Macros.h"
#include <SFML/Graphics.hpp>


namespace RandomPath
{
	std::vector<NextStep> calc_path(Map * map, Enemy * m_enemie);
	void update_curr_location(sf::Vector2f& curr_location_with_steps, NextStep next);
	bool is_dir_avaliable(NextStep next, std::vector<NextStep> avaliable);
};



