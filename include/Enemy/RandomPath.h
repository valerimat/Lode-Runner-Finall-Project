#pragma once
#include <vector>
class Map;
#include "Macros.h"
#include <SFML/Graphics.hpp>


class RandomPath
{
public:
	RandomPath() = default;
	std::vector<NextStep> calc_path(Map map, sf::Vector2f curr_location,float height, float width);
	std::vector<NextStep> get_avaliable_steps(Map map, sf::Vector2f curr_location, sf::Vector2f bottomRight, sf::Vector2f bottomLeft);
	void advance_location(NextStep step, sf::Vector2f& curr_location, sf::Vector2f& bottomLeft, sf::Vector2f& bottomRight);
	int in_avaliable(NextStep step, std::vector<NextStep> vec);
};



