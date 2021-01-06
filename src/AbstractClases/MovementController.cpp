#include "MovementController.h"
#include "Map.h"


MovementController::MovementController(Map* map) :
	m_map(map)
{};


std::vector<NextStep> MovementController::get_avaliable_steps(sf::Vector2f location)
{
	//getting all 4 bounding corners
	std::vector<NextStep> avaliable_steps;
	sf::Vector2f top_left = location;


	bool can_move_up = able_to_move_up(top_left, 40);
	bool can_move_left = able_to_move_side(NextStep::LEFT, top_left);
	bool can_move_right = able_to_move_side(NextStep::RIGHT, top_left);
	bool can_move_down = able_to_move_down(top_left);

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





bool MovementController::we_are_on_ladder( sf::Vector2f location)
{
	if (m_map->we_are_on_ladder(location))
		return true;

	return false;
}

bool MovementController::able_to_move_up(sf::Vector2f topLeft, float size)
{
	if (we_are_on_ladder(topLeft)) {
		if (there_is_no_wall_above(topLeft))
			return true;
	}
	return false;
}

bool MovementController::there_is_no_wall_above(sf::Vector2f topLeft)
{
	//need to convert to check only for ground
	if (!m_map->is_there_ground(topLeft + sf::Vector2f(1, -1))
		&& !m_map->is_there_ground(topLeft + sf::Vector2f(39, -1)))
		return true;

	return false;
}


bool  MovementController::able_to_move_side(NextStep side, sf::Vector2f topLeft)
{
	sf::Vector2f offset;
	sf::Vector2f bottom_left(topLeft.x, topLeft.y + 37);

	if (topLeft.x - 5 < 0)
		return false;
	//later add variable
	else if (topLeft.x + 5 > 800)
		return false;

	if (side == NextStep::LEFT)
		offset = sf::Vector2f(-1, 0);
	else
		offset = sf::Vector2f(41, 0);


	if (m_map->is_there_ground(topLeft + offset))
		return false;
	if (m_map->is_there_ground(bottom_left + offset))
		return false;

	if (we_are_on_rope(topLeft))
		return true;

	if (m_map->we_are_on_ladder(topLeft))
		return true;

	if (m_map->is_there_ground(topLeft + sf::Vector2f(0, 41))
		|| m_map->is_there_ground(topLeft + sf::Vector2f(40, 41)))
		return true;


	return false;
}

bool MovementController::we_are_on_rope(sf::Vector2f topLeft)
{
	//move it from the map
	if (m_map->we_are_hanging_on_rope(topLeft, topLeft + sf::Vector2f(40, 0)))
	{
		return true;
	}
	return false;
}

bool  MovementController::able_to_move_down(sf::Vector2f topLeft)
{

	if (m_map->is_there_ground(topLeft + sf::Vector2f(1, 41))
		|| m_map->is_there_ground(topLeft + sf::Vector2f(39, 41)))
		return false;

	return true;
}