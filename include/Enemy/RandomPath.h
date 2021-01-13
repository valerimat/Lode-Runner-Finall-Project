#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include "Algo.h"
class Graph;
class EnemyController;
class Map;
class Enemy;

/*
Algorithm to move to one side
*/
class RandomPath :public Algo
{
public:
	//Main call function:
	std::vector<sf::Vector2f> calc_path(Graph& graph, sf::FloatRect& our_rect) override;
private:

};