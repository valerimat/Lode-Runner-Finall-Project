#include "RandomPath.h"
#include "Map.h"
#include "time.h"
#include "Enemy.h"

std::vector<NextStep> RandomPath::calc_path(Map* map, Enemy* enemy)
{
	srand((unsigned)time(NULL));

	sf::Vector2f starting_loc = enemy->get_location();

	std::vector<NextStep> steps;

	std::vector<NextStep> avaliable_steps = enemy->get_avaliable_steps(map, starting_loc);

	int random = 0;
	int modulo = 0;
	int i = 0;

	while (1)
	{
		if (is_dir_avaliable(NextStep::UP, avaliable_steps))
			avaliable_steps.push_back(NextStep::UP);

		modulo = avaliable_steps.size();

		if (avaliable_steps.size() == 0)
		{
			avaliable_steps.push_back(NextStep::NONE);
			return avaliable_steps;
		}

		random = rand() % modulo;

		

		steps.push_back(avaliable_steps[random]);

		update_curr_location(starting_loc, avaliable_steps[random]);

		if (steps.size() > 40)
			break;

		avaliable_steps.clear();

		avaliable_steps = enemy->get_avaliable_steps(map, starting_loc);
		i = 0;
		while (i < 5)
		{
			if (is_dir_avaliable(steps[steps.size() - 1], avaliable_steps))
			{
				NextStep same = steps[steps.size() - 1];
				steps.push_back(same);
				update_curr_location(starting_loc, same);
			}
			else
				break;
			avaliable_steps.clear();
			avaliable_steps = enemy->get_avaliable_steps(map, starting_loc);
			++i;
		}
	}
	return steps;
}

void RandomPath::update_curr_location(sf::Vector2f & curr_location_with_steps, NextStep next)
{
	sf::Vector2f offset(0, 0);
	switch (next)
	{
	case NextStep::UP:
		offset.y -= STEP;
		break;

	case NextStep::DOWN:
		offset.y += STEP;
		break;

	case NextStep::LEFT:
		offset.x -= STEP;
		break;

	case NextStep::RIGHT:
		offset.x += STEP;
		break;
	}	

	curr_location_with_steps += offset;
}

bool RandomPath::is_dir_avaliable(NextStep next, std::vector<NextStep> avaliable)
{
	for (int i = 0; i < avaliable.size(); ++i)
	{
		if (avaliable[i] == next)
			return true;
	}

	return false;
}