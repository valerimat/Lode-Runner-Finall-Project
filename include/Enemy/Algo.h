#pragma once
#include <vector>
#include "Macros.h"
#include "SFML/Graphics.hpp"
class Graph;
class Map;
class EnemyController;


class Algo
{
public:
	// c-tor
	Algo() = default;

	// virtual func
	virtual std::vector<sf::Vector2f> calc_path(Graph& graph, sf::Vector2f our_location, sf::Vector2f wanted_location) =0;
private:
};