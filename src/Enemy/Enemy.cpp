#include "Enemy.h"
#include "Map.h"



IQ Enemy::get_iq()
{
	return m_iq;
}

void Enemy::set_path(std::vector<NextStep> steps)
{
	m_path = steps;
}

void Enemy::move()
{
	NextStep step = m_path[0];

	if (m_path.size() == 1)
		m_path.clear();
	else
	m_path.erase(m_path.begin());
	
	switch (step)
	{
	case NextStep::LEFT:
		update_location(NextStep::LEFT);
		break;
	case NextStep::RIGHT:
		update_location(NextStep::RIGHT);
		break;
	case NextStep::UP:
		update_location(NextStep::UP);
		break;
	case NextStep::DOWN:
		update_location(NextStep::DOWN);
		break;

	default:
		break;
	}

	m_sprite.setPosition(m_location);
}


void Enemy::set_smartness()
{
	int random = rand() % 3;

	m_iq = IQ(random);
}


std::vector<NextStep> Enemy::get_avaliable_steps(Map* map,sf::Vector2f location)
{
	//getting all 4 bounding corners
	std::vector<NextStep> avaliable_steps;
	sf::Vector2f top_left = location;
	sf::Vector2f top_right(top_left.x + get_width(), top_left.y);
	sf::Vector2f bottom_left(top_left.x, top_left.y +get_height());
	sf::Vector2f bottom_right(bottom_left.x + get_width(), bottom_left.y);

	sf::Vector2f offset_left(-5, 0);
	sf::Vector2f offset_right(5, 0);
	sf::Vector2f offset_up(0, -5);
	sf::Vector2f offset_down(0, 5);
	
	char state = get_curr_state(map, location);

	switch (state)
	{
	case GROUND:

		if (we_are_on_ladder(*map, top_left))
		{
			avaliable_steps.push_back(NextStep::UP);

			if((*map).what_is_there(top_left + offset_left) != GROUND)
				avaliable_steps.push_back(NextStep::LEFT);
			if ((*map).what_is_there(top_right + offset_right) != GROUND)
				avaliable_steps.push_back(NextStep::RIGHT);
		}
		if ((*map).what_is_there(top_left + offset_left) != GROUND)
			avaliable_steps.push_back(NextStep::LEFT);
		if ((*map).what_is_there(top_right + offset_right) != GROUND)
			avaliable_steps.push_back(NextStep::RIGHT);
		break;

	case POLE:
		if ((*map).we_are_hanging_on_rope(top_left, top_right))
		{
			if ((*map).what_is_there(top_left + offset_left) != GROUND)
				avaliable_steps.push_back(NextStep::LEFT);
			if ((*map).what_is_there(top_right + offset_right) != GROUND)
				avaliable_steps.push_back(NextStep::RIGHT);
		}
		avaliable_steps.push_back(NextStep::DOWN);
		break;

	case LADDER:
		if ((*map).is_ladder(top_left) == LADDER)
		{
			if ((*map).what_is_there(bottom_left + offset_down) != GROUND &&
				(*map).what_is_there(bottom_right + offset_down))
			{
				avaliable_steps.push_back(NextStep::DOWN);
			}

			if ((*map).what_is_there(top_left + offset_up) != GROUND &&
				(*map).what_is_there(top_right + offset_up)!= GROUND )
			{
				avaliable_steps.push_back(NextStep::UP);
			}
		}
		avaliable_steps.push_back(NextStep::UP);
		if ((*map).what_is_there(top_left + offset_left) != GROUND)
			avaliable_steps.push_back(NextStep::LEFT);
		if ((*map).what_is_there(top_right + offset_right) != GROUND)
			avaliable_steps.push_back(NextStep::RIGHT);
		break;

	//nothing bellow we can only fall
	case NONE:
		avaliable_steps.push_back(NextStep::DOWN);

		break;

	}
	/*
	if ((*map).we_are_hanging_on_rope(top_left, top_right))
	{
		if ((*map).what_is_there(top_left + offset_left) != GROUND)
			avaliable_steps.push_back(NextStep::LEFT);
		if ((*map).what_is_there(top_right + offset_right) != GROUND)
			avaliable_steps.push_back(NextStep::RIGHT);
	}
	*/

	return avaliable_steps;
}


bool Enemy::path_is_empty()
{
	if (m_path.size() == 0)
		return true;

	return false;
}


char Enemy::get_curr_state(Map* map, sf::Vector2f   location)
{
	sf::Vector2f top_left = location;
	sf::Vector2f top_right(top_left.x + get_width(), top_left.y);
	sf::Vector2f bottom_left(top_left.x, top_left.y + get_height());
	sf::Vector2f bottom_right(bottom_left.x + get_width(), bottom_left.y);

	char bottom_left_char = (*map).what_is_there(bottom_left);
	char bottom_right_char = (*map).what_is_there(bottom_right);
	char top_left_char = (*map).what_is_there(top_left);
	char top_right_char = (*map).what_is_there(top_right);


	char bottom_left_char_ground = (*map).what_is_there(sf::Vector2f(bottom_left.x, bottom_left.y + 1));
	char bottom_right_char_ground = (*map).what_is_there(sf::Vector2f(bottom_right.x, bottom_right.y + 1));

	if(bottom_left_char_ground == GROUND || bottom_right_char_ground == GROUND)
		return GROUND;

	if (top_left_char == LADDER || top_right_char == LADDER
		||bottom_left_char == LADDER || bottom_right_char == LADDER)
		return LADDER;

	if ((top_left_char == POLE || top_right_char == POLE ))
		return POLE;
	

		return NONE;
}

bool Enemy::we_are_on_ladder(Map& map, sf::Vector2f location)
{
	if (map.collision_top_right(location) == LADDER)
		return true;

	else
		return false;
}