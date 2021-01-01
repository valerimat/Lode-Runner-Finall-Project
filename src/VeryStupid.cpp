#include "VeryStupid.h"
#include "Map.h"

std::vector<NextStep> VeryStupid::calc_path(Map map, sf::Vector2f curr_location)
{
	std::vector<NextStep> steps;

	NextStep next;

	sf::Vector2f curr_location_with_steps = curr_location;
	//int side = rand() % 2;

//	if (side == 0)
	//	next = NextStep::LEFT;
	//else
		//next = NextStep::RIGHT;

	next = NextStep::RIGHT;
	//untill filing the vector
	while (1)
	{
		if (!next_step_is_valid(map,next, curr_location_with_steps))
		{
			if (next == NextStep::LEFT)
			{
				next = NextStep::RIGHT;
			}
			else
			{
				next = NextStep::LEFT;
			}
		}

		steps.push_back(next);

		if (steps.size() == 20)
			return steps;

		update_curr_location(curr_location_with_steps, next);
		
	}
	
}

bool VeryStupid::next_step_is_valid(Map map,NextStep next, sf::Vector2f curr_location_with_steps)
{
	char bellow = map.what_is_there_bellow(curr_location_with_steps);
	char side = map.what_is_there_on_the_side(curr_location_with_steps);

	if (bellow == NONE || bellow == POLE)
		return false;
	if (side == GROUND)
		return false;
	return true;
}

void VeryStupid::update_curr_location(sf::Vector2f curr_location_with_steps, NextStep next)
{
	if (next == NextStep::LEFT)
		curr_location_with_steps.x -= 2;
	else
		curr_location_with_steps.x += 2;
}