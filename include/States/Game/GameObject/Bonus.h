#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Macros.h"
#include "SFML/Graphics.hpp"

class Map;

class Bonus
{
public:
	Bonus() = default;
	virtual void Surprise(Map *map) = 0;
private:
};