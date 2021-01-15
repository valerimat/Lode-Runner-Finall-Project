#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include "Graph.h"
#include "EnemyController.h"
#include "Node.h"

std::vector<sf::Vector2f> OneSide::calc_path(Graph& graph, sf::Vector2f our_location, sf::Vector2f wanted_location)
{
	std::vector<sf::Vector2f> waypoints;
	Node* node = graph.get_closest_node(our_location);
	
	//first_we_pus_closest_node
	waypoints.push_back(node->get_location());
	//std::cout << "location = " << "( " << node->get_location().x << " " << node->get_location().y << " )" << std::endl;
	sf::Vector2f next_location;

	srand(time(0));

	int random = rand();
	
	if (random %2 ==0)
		next_location = get_most_left(node);
	else
		next_location = get_most_right(node);

	waypoints.push_back(next_location);

	//get_most_left
	return waypoints;
}
//-----------------------------------------------------------------------------



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

