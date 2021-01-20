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

protected:
	Map* m_map = nullptr;
};