#include "RandomPath.h"
#include "Map.h"
#include "time.h"
std::vector<NextStep> RandomPath::calc_path(Map map, sf::Vector2f curr_location, float height, float width)
{
	srand((unsigned)time(NULL));
	std::vector<NextStep> steps;
	std::vector<NextStep> avaliable_steps;


	sf::Vector2f bottomRight(curr_location.x + width, curr_location.y + height);
	sf::Vector2f bottomLeft(curr_location.x, curr_location.y + height);
	
	NextStep last_step = NextStep::UP;

	int modulo = 0;
	int random = 0;
	int counter = 0;

	while (1)
	{
		
		avaliable_steps.clear();

		avaliable_steps = get_avaliable_steps(map, curr_location, bottomRight, bottomLeft);
		
		modulo = avaliable_steps.size();

		if (in_avaliable(last_step,avaliable_steps) != -1 && counter !=5 && steps.size() != 0)
		{
			random = in_avaliable(last_step, avaliable_steps);
			counter++;
		}
		else 
		{
			random = rand() % modulo;

			if (counter == 5)
				counter = 0;
		}

		steps.push_back(avaliable_steps[random]);

		advance_location(avaliable_steps[random], curr_location, bottomLeft, bottomRight);

		auto num_of_steps = steps.size();

		last_step = steps[num_of_steps - 1];

		if (counter == 5)
			counter = 0;

		if (steps.size() == 40)
			break;
		
	}
	return steps;
}

int RandomPath::in_avaliable(NextStep step, std::vector<NextStep> vec)
{
	int i = 0;
	while (i < vec.size())
	{
		if (step == vec[i])
			return i;

		++i;
	}
	return -1;
}


std::vector<NextStep> RandomPath::get_avaliable_steps(Map map, sf::Vector2f curr_location, sf::Vector2f bottomRight, sf::Vector2f bottomLeft){
	std::vector<NextStep> avaliable_steps;

	char collisionTop = map.collision_top_right(curr_location);
	char collisionLeft = map.what_is_there_on_the_side(bottomLeft);
	char collisionRight = map.what_is_there_on_the_side(bottomRight);

	if (collisionTop == NONE)
	{
		if (collisionLeft != GROUND) 
		{
			avaliable_steps.push_back(NextStep::DOWN);
			return avaliable_steps;
		}
	}

	if (collisionTop == LADDER || collisionLeft == LADDER)
	{
		if (collisionLeft != GROUND )
		{
			//avaliable_steps.push_back(NextStep::LEFT);
			avaliable_steps.push_back(NextStep::UP);
			avaliable_steps.push_back(NextStep::DOWN);
		}
		else if (collisionLeft == LADDER) {
			if(collisionTop != LADDER)
				avaliable_steps.push_back(NextStep::DOWN);
			else
				avaliable_steps.push_back(NextStep::UP);
		}
		else
		{
			avaliable_steps.push_back(NextStep::UP);
		}
	}
	
		bottomRight.y -= 40;

		char collisionTopleft = map.what_is_there_on_the_side(curr_location);
	    char collisionTopRight = map.what_is_there_on_the_side(bottomRight);

		if(collisionTopleft != GROUND)
		avaliable_steps.push_back(NextStep::LEFT);

		if (collisionTopRight != GROUND)
		avaliable_steps.push_back(NextStep::RIGHT);

	
	return avaliable_steps;
}



void RandomPath::advance_location(NextStep step, sf::Vector2f& curr_location, sf::Vector2f& bottomLeft, sf::Vector2f& bottomRight)
{
	sf::Vector2f offset(0, 0);

	switch (step)
	{
	case NextStep::UP:
		offset.y -= 5;

		break;
	case NextStep::DOWN:
		offset.y += 5;
		break;
	case NextStep::LEFT:
		offset.x -= 5;
		break;
	case NextStep::RIGHT:
		offset.x += 5;
		break;
	default:
		break;
	}

	curr_location += offset;
	bottomLeft += offset;
	bottomRight += offset;

}