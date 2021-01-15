#include "RandomPath.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include "Graph.h"
#include "EnemyController.h"
#include "Node.h"
#include<ctime>

std::vector<sf::Vector2f> RandomPath::calc_path(Graph& graph, sf::Vector2f our_location, sf::Vector2f wanted_location)
{
	std::vector<sf::Vector2f> waypoints;

	Node* node = graph.get_closest_node(our_location);

	//first_we_pus_closest_node
	waypoints.push_back(node->get_location());

	find_random_path(node, waypoints);


	return waypoints;

}
//-----------------------------------------------------------------------------

void RandomPath::find_random_path(Node* node, std::vector<sf::Vector2f>& waypoints)
{
	srand(time(NULL));

	Node* next;
	next = node->get_random_neigbor(rand());

	for (int i = 0; i < 10; ++i)
	{
		
		waypoints.push_back(next->get_location());
		next = next->get_random_neigbor(rand());
	}
}
