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

void Enemy::move(float dt)
{
	NextStep step = m_path[0];

	if (m_path.size() == 1)
		m_path.clear();
	else
	m_path.erase(m_path.begin());
	
	switch (step)
	{
	case NextStep::LEFT:
		update_location(NextStep::LEFT,dt);
		break;
	case NextStep::RIGHT:
		update_location(NextStep::RIGHT,dt);
		break;
	case NextStep::UP:
		update_location(NextStep::UP,dt);
		break;
	case NextStep::DOWN:
		update_location(NextStep::DOWN,dt);
		break;
	case NextStep::NONE:
		break;
	default:
		break;
	}

	m_sprite.setPosition(m_location);
}


void Enemy::set_smartness(int i )
{
	//srand(time(NULL));

	//int random = rand() % 3;

	m_iq = IQ(i);
}


std::vector<NextStep> Enemy::get_avaliable_steps(Map* map,sf::Vector2f location)
{
	//getting all 4 bounding corners
	std::vector<NextStep> avaliable_steps;
	sf::Vector2f top_left = location;

	
	bool can_move_up = able_to_move_up(top_left,40,*map);
	bool can_move_left = able_to_move_side(NextStep::LEFT, top_left, map);
	bool can_move_right = able_to_move_side(NextStep::RIGHT, top_left, map);
	bool can_move_down = able_to_move_down(top_left, map);
	
	if (can_move_up)
		avaliable_steps.push_back(NextStep::UP);
	if (can_move_left)
		avaliable_steps.push_back(NextStep::LEFT);
	if (can_move_right)
		avaliable_steps.push_back(NextStep::RIGHT);
	if (can_move_down)
		avaliable_steps.push_back(NextStep::DOWN);

	return avaliable_steps;
	
}


bool Enemy::path_is_empty()
{
	if (m_path.size() == 0)
		return true;

	return false;
}


bool Enemy::we_are_on_ladder(Map& map, sf::Vector2f location)
{
	if (map.IsOnLadder(location))
		return true;

	return false;
}

bool Enemy::able_to_move_up(sf::Vector2f topLeft, float size, Map & map)
{
	if (we_are_on_ladder(map, topLeft)) {
		if (there_is_no_wall_above(topLeft, map))
			return true;
	}
	return false;
}

bool Enemy::there_is_no_wall_above(sf::Vector2f topLeft, Map& map)
{
	//need to convert to check only for ground
	if (!map.IsOnGround(topLeft + sf::Vector2f(1, -1))
		&& !map.IsOnGround(topLeft + sf::Vector2f(39, -1)))
		return true;

	return false;
}


bool  Enemy::able_to_move_side(NextStep side, sf::Vector2f topLeft, Map *map)
{
	sf::Vector2f offset;
	sf::Vector2f bottom_left(topLeft.x, topLeft.y + 39);

	if (topLeft.x - 5 < 0)
		return false;
	//later add variable
	else if (topLeft.x + 5 > 800)
		return false;

	if (side == NextStep::LEFT)
		offset = sf::Vector2f(-1, 0);
	else
		offset = sf::Vector2f(41, 0);

	
	if (map->IsOnGround(topLeft + offset))
		return false;
	if (map->IsOnGround(bottom_left + offset))
		return false;
	
	if (we_are_on_rope(topLeft, map))
		return true;

	if (map->IsOnLadder(topLeft))
		return true;

	if (map->IsOnGround(topLeft + sf::Vector2f(0, 41))
		|| map->IsOnGround(topLeft + sf::Vector2f(40, 41)))
			return true ;


	
	return false;
}

bool Enemy::we_are_on_rope(sf::Vector2f topLeft, Map* map)
{
	//move it from the map
	if (map->IsOnRope(topLeft, topLeft + sf::Vector2f(40, 0)))
	{
		return true;
	}
	return false;
}

bool  Enemy::able_to_move_down( sf::Vector2f topLeft, Map* map)
{

	if (map->IsOnGround(topLeft + sf::Vector2f(1, 41))
		|| map->IsOnGround(topLeft + sf::Vector2f(39, 41)))
		return false;

	return true;
}