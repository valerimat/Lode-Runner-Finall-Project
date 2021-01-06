#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include "EnemyController.h"

std::vector<NextStep> OneSide::calc_path(Map * map,EnemyController & controller,sf::Vector2f  curr_loc)
{
	

	srand(time(NULL));

	std::vector<NextStep> steps;

	sf::Vector2f curr_location = curr_loc;

	std::vector<NextStep> next_avaliable = controller.get_avaliable_steps(curr_location);

	sf::Vector2f curr_location_with_steps = curr_location;

	NextStep dir = NextStep::NONE;

	int random = rand() % 2;
	int i = 0;

	if (random == 0)
	{
		while (i < next_avaliable.size())
		{
			if (next_avaliable[i] == NextStep::LEFT)
			{
				dir = NextStep::LEFT;
				break;
			}
			++i;
		}
		if (dir == NextStep::NONE)
			NextStep::RIGHT;
	}
	else
	{
		while (i < next_avaliable.size())
		{
			if (next_avaliable[i] == NextStep::RIGHT)
			{
				dir = NextStep::RIGHT;
				break;
			}
			++i;
		}
		if (dir == NextStep::NONE)
			NextStep::LEFT;
	}

	while (1)
	{
	
		update_curr_location(curr_location_with_steps, dir);
		
		next_avaliable = controller.get_avaliable_steps(curr_location_with_steps);
		if (is_dir_avaliable(dir, next_avaliable))
		{
			if (is_there_still_floor(dir, map, curr_location_with_steps, 40))
			steps.push_back(dir);
			else
			{
				if (is_opposide_avaliable(dir, next_avaliable))
				{
					if (dir == NextStep::LEFT)
					{
						dir = NextStep::RIGHT;
						steps.push_back(dir);
					}
					else
					{
						dir = NextStep::LEFT;
						steps.push_back(dir);
					}
				}
			}

		}
		else
		{
			if (is_opposide_avaliable(dir, next_avaliable))
			{
				if(dir == NextStep::LEFT)
				{ 
					dir = NextStep::RIGHT;
					steps.push_back(dir);
				}
				else
				{
					dir = NextStep::LEFT;
					steps.push_back(dir);
				}
			}
		}
		
		if (steps.size() == 40)
			break;
	}
	return steps;
}
//-----------------------------------------------------------------------------

bool OneSide::is_there_still_floor(NextStep next,
								   Map * map,
	                               sf::Vector2f &curr_location_with_steps,
	                               float height)
{
	sf::Vector2f loc = curr_location_with_steps;
	update_curr_location(loc, next);

	if (next == NextStep::LEFT)
	{
		if ((*map).what_is_there(sf::Vector2f(loc.x, loc.y + height +1)) == GROUND)
			return true;
		return false;
	}
	else
	{
		if ((*map).what_is_there(sf::Vector2f(loc.x + height, loc.y + height + 1)) == GROUND)
			return true;

		return false;
	}
	return false;
}
//-----------------------------------------------------------------------------

bool OneSide::is_dir_avaliable(NextStep next, std::vector<NextStep> avaliable)
{
	for (int i = 0; i < avaliable.size(); ++i)
	{
		if (avaliable[i] == next)
			return true;
	}

	return false;
}
//-----------------------------------------------------------------------------

bool OneSide::is_opposide_avaliable(NextStep next, std::vector<NextStep> avaliable)
{
	NextStep check_for;
	if (next == NextStep::LEFT)
		check_for = NextStep::RIGHT;
	else
		check_for = NextStep::LEFT;

	for (int i = 0; i < avaliable.size(); ++i)
	{
		if (avaliable[i] == check_for)
			return true;
	}

	return false;
}
//-----------------------------------------------------------------------------



void OneSide::update_curr_location(sf::Vector2f & curr_location_with_steps, NextStep next)
{
	if (next == NextStep::LEFT)
		curr_location_with_steps.x -= STEP;
	else
		curr_location_with_steps.x += STEP;
}