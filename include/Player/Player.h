#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicObject.h"
#include "Lives.h"
#include "PlayerController.h"
#include <vector>
#include "Macros.h"

class Player : public DynamicObject
{
public:

	using DynamicObject::DynamicObject;

	//Lives* get_lives();

	//PlayerController * get_controller();
	std::vector <NextStep> GetValid();
	void Move(sf::Keyboard::Key key,float dt);
	void SetValid(std::vector <NextStep> valid_steps);
private:
	Lives m_lives;
	std::vector <NextStep> m_valid_steps;
	//PlayerController * get_controller();
};
