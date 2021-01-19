#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include "Graph.h"
#include "EnemyController.h"
#include "Node.h"
#include <random>

std::vector<sf::Vector2f> OneSide::CalcPath(Graph& graph, sf::Vector2f our_location, sf::Vector2f wanted_location)
{
	auto random = std::random_device();

	std::vector<sf::Vector2f> waypoints;
	Node* node = graph.GetClosestNode(our_location);
	if (node == nullptr)
	{
		waypoints.push_back(our_location);
		return waypoints;
	}

	//first_we_pus_closest_node
	//waypoints.push_back(node->get_location());
	
	sf::Vector2f next_location;


	int random_number = random();
	
	if (random_number % 2 == 0)
	{
		next_location = GetMostLeft(node);
		if (next_location == node->get_location())
			next_location = GetMostRight(node);
	}
	else
	{
		next_location = GetMostRight(node);
		if (next_location == node->get_location())
			next_location = GetMostLeft(node);
	}
	
	

	waypoints.push_back(next_location);

	//get_most_left
	return waypoints;
}
//-----------------------------------------------------------------------------

sf::Vector2f OneSide::GetMostLeft(Node* node)
{
	Node* temp = node;
	Node* next;
	while (1)
	{

		next = temp->GetLeft();

		//if the next node is fall node we dont want it
		if (next == nullptr)
			break;

		if (next->GetRight() == nullptr)
			break;

		temp = temp->GetLeft();
		
		if (temp == nullptr)
			break;
	}

	return temp->get_location();
}
//-----------------------------------------------------------------------------

sf::Vector2f OneSide::GetMostRight(Node* node)
{
	Node* temp = node;
	Node* next;
	while (1)
	{
		next = temp->GetRight();
		if (next == nullptr)
			break;
		//if the next node is fall node we dont want it
		if (next->GetLeft() == nullptr)
			break;

		temp = temp->GetRight();

		if (temp == nullptr)
			break;
	}

	return temp->get_location();
}
//-----------------------------------------------------------------------------
