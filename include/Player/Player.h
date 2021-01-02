#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicObject.h"
#include "Lives.h"
#include "PlayerController.h"

class Player : public DynamicObject
{
public:

	using DynamicObject::DynamicObject;

	//Lives* get_lives();

	//PlayerController * get_controller();

	void move(sf::Keyboard::Key key);

private:
	Lives m_lives;
	//PlayerController * get_controller();
};
