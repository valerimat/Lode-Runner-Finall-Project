#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Macros.h"
class Map;


class MovementController
{
public:
	//Ctors:
	MovementController(Map* map);

	std::vector<NextStep> get_avaliable_steps(sf::Vector2f location);
	
protected:
	//used to check next steps
	bool we_are_on_ladder( sf::Vector2f location);
	bool able_to_move_up(sf::Vector2f topLeft, float size);
	bool there_is_no_wall_above(sf::Vector2f topLeft);
	bool able_to_move_side(NextStep side, sf::Vector2f topLeft);
	bool we_are_on_rope(sf::Vector2f topLeft);
	bool able_to_move_down(sf::Vector2f topLeft);

	Map* m_map = nullptr;
};