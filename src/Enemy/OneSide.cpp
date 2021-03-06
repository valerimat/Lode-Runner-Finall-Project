#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include "Graph.h"
#include "EnemyController.h"
#include "Node.h"
#include <random>

//=============================================================================
std::vector<sf::Vector2f> OneSide::calc_path(Graph& graph,
											 sf::Vector2f our_location,
	                                         sf::Vector2f wanted_location)
{
	auto random = std::random_device();

	std::vector<sf::Vector2f> waypoints;
	Node* node = graph.get_closest_node(our_location);
	if (node == nullptr)
	{
		waypoints.push_back(our_location);
		return waypoints;
	}

	sf::Vector2f next_location;

	int random_number = random();
	
	//setting either all left all right
	if (random_number % 2 == 0)
	{
		next_location = get_most_left(node);
		if (next_location == node->get_location())
			next_location = get_most_right(node);
	}
	else
	{
		next_location = get_most_right(node);
		if (next_location == node->get_location())
			next_location = get_most_left(node);
	}
	waypoints.push_back(next_location);

	//get_most_left
	return waypoints;
}
//=============================================================================

//=============================================================================
sf::Vector2f OneSide::get_most_left(Node* node)
{
	Node* temp = node;
	Node* next;
	while (1)
	{

		next = temp->get_left();

		//if the next node is fall node we dont want it
		if (next == nullptr)
			break;

		if (next->get_right() == nullptr)
			break;

		temp = temp->get_left();
		
		if (temp == nullptr)
			break;
	}

	return temp->get_location();
}
//=============================================================================

//=============================================================================
sf::Vector2f OneSide::get_most_right(Node* node)
{
	Node* temp = node;
	Node* next;
	while (1)
	{
		next = temp->get_right();
		if (next == nullptr)
			break;
		//if the next node is fall node we dont want it
		if (next->get_left() == nullptr)
			break;

		temp = temp->get_right();

		if (temp == nullptr)
			break;
	}

	return temp->get_location();
}
//=============================================================================
