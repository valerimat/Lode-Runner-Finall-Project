#include "RandomPath.h"
#include "Map.h"
#include "Enemy.h"
#include <iostream>
#include "Graph.h"
#include "EnemyController.h"
#include<ctime>

std::vector<sf::Vector2f> RandomPath::calc_path(Graph& graph, sf::FloatRect& our_rect)
{
	
	srand(time(0));
	std::vector<sf::Vector2f> next;
	sf::Vector2f waypoint(-1, -1);
	int index = graph.we_are_on_node(our_rect);
	if (index == -1)
	{
		sf::Vector2f edge = graph.we_are_on_edge(our_rect);
		
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
		waypoint = graph.get_random_neighboor(index, rand());
	}
	next.push_back(waypoint);

	return next;
}
//-----------------------------------------------------------------------------

