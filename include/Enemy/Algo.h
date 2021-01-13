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
	Algo() = default;
	virtual std::vector<sf::Vector2f> calc_path(Graph& graph, sf::FloatRect& our_rect) =0;
private:
};