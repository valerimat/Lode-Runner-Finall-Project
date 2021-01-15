#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include "Algo.h"
class Node;
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
	std::vector<sf::Vector2f> calc_path(Graph& graph, sf::Vector2f our_rect, sf::Vector2f wanted_location) override;
private:
	void find_random_path(Node* node, std::vector<sf::Vector2f>& waypoints);
};