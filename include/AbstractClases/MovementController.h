#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "Music.h"
class Map;


class MovementController
{
public:
	//Ctors:
	MovementController(Map* map);
	virtual void init_controller() = 0;
	virtual void move(float dt) = 0;

protected:
	Map* m_map = nullptr;
};