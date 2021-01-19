#include "RandomPath.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include "Graph.h"
#include "EnemyController.h"
#include "Node.h"
#include <random>

std::vector<sf::Vector2f> RandomPath::CalcPath(Graph& graph, sf::Vector2f our_location, sf::Vector2f wanted_location)
{
	std::vector<sf::Vector2f> waypoints;

	Node* node = graph.GetClosestNode(our_location);
	if (node == nullptr)
	{
		waypoints.push_back(our_location);
		return waypoints;
	}

	//first_we_pus_closest_node
	waypoints.push_back(node->get_location());

	FindRandomPath(node, waypoints);


	return waypoints;

}
//-----------------------------------------------------------------------------

void RandomPath::FindRandomPath(Node* node, std::vector<sf::Vector2f>& waypoints)
{
	auto random = std::random_device();
	
	Node* next;
	next = node->GetRandomNeighbor(random());

	for (int i = 0; i < 10; ++i)
	{
		
		waypoints.push_back(next->get_location());
		next = next->GetRandomNeighbor(rand());
	}
}
//-----------------------------------------------------------------------------
