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
	char get_curr_state(Map * map, sf::Vector2f location);

private:
	bool we_are_on_ladder(Map& map, sf::Vector2f location);
	std::vector<NextStep> m_path;
	IQ m_iq;

};