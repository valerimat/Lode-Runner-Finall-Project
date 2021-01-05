#pragma once
#include "DynamicObject.h"
#include "Macros.h"
class Map;

class Enemy : public DynamicObject
{
public:
	using DynamicObject::DynamicObject;
	IQ get_iq();
	virtual void set_smartness();
	void set_path(std::vector<NextStep> steps);
	std::vector<NextStep> get_avaliable_steps(Map * map, sf::Vector2f location);
	void move();
	bool path_is_empty();
	
	bool there_is_no_wall_above(sf::Vector2f topLeft, Map& map);
	bool  able_to_move_up(sf::Vector2f topLeft, float size, Map& map);
	bool  able_to_move_side(NextStep side, sf::Vector2f topLeft, Map* map);
	bool  able_to_move_down(sf::Vector2f topLeft, Map* map);
	bool we_are_on_rope(sf::Vector2f topLeft, Map* map);


private:
	bool we_are_on_ladder(Map& map, sf::Vector2f location);
	std::vector<NextStep> m_path;
	IQ m_iq;

};