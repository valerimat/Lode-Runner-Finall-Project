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
class OneSide :public Algo
{
public:
	//Main call function:
	std::vector<sf::Vector2f> CalcPath(Graph & graph, sf::Vector2f our_location, sf::Vector2f wanted_location) override;
private:
	sf::Vector2f GetMostLeft(Node* node);
	sf::Vector2f GetMostRight(Node* node);
};