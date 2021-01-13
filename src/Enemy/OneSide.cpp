#include "OneSide.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include "Graph.h"
#include "EnemyController.h"

std::vector<sf::Vector2f> OneSide::calc_path(Graph& graph, sf::FloatRect& our_rect)
{
	srand(time(NULL));
	std::vector<sf::Vector2f> next;
	
	sf::Vector2f waypoint(-1,-1);
	int index = graph.we_are_on_node(our_rect);
	if (index == -1)
	{
		sf::Vector2f edge = graph.we_are_on_edge_hori(our_rect);
		if (edge != sf::Vector2f(-1, -1))
		{
			auto random = rand() % 2;

			if (random == 1)
			{
				waypoint = graph.get_parent_node(edge.x);
			}
			else
			{
				waypoint = graph.get_neighboor_node(edge.x, edge.y);
			}
		}
	}
	else
	{
		auto random = rand() % 2;

		if (random == 1)
		{
			waypoint = graph.get_max_left_node(index);
			if(waypoint == sf::Vector2f(-1,-1))
				waypoint = graph.get_max_right_node(index);
		}
		else
		{
			waypoint = graph.get_max_right_node(index);
			if (waypoint == sf::Vector2f(-1, -1))
				waypoint = graph.get_max_left_node(index);
		}
	}
	next.push_back(waypoint);

	return next;
}
//-----------------------------------------------------------------------------
