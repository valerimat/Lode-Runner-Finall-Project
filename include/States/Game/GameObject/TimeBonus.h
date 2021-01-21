#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Bonus.h"
#include "Macros.h"
#include "SFML/Graphics.hpp"
#include "Map.h"

class TimeBonus :public Bonus
{
public:
	//Main call function:
	void Surprise(Map *map)override;
private:
};