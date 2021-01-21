#include "Bfs.h"
#include "Graph.h"
#include "Node.h"
#include <iostream>
#include "MacroSettings.h"

//=============================================================================
std::vector<sf::Vector2f> Bfs::calc_path(Graph& graph,
	                                     sf::Vector2f our_location,
	                                     sf::Vector2f wanted_location)
{
	std::vector<sf::Vector2f> waypoints;
	Node* from, * to;

	from =  graph.get_closest_node(our_location);

	//For safety:
	if (from == nullptr)
	{
		waypoints.push_back(our_location);
		return waypoints;
	}

	to = graph.get_closest_node(wanted_location);
	if (to == nullptr)
	{ 
		sf::Vector2f off(0, - MacroSettings::get_settings().get_scale_width()*50);
		wanted_location += off;
		to = graph.get_closest_node((wanted_location));
	}


	//from the BFS we will get set of waypoints to get to the player:
	waypoints = BFS(from, to);

	graph.Clean();

	return waypoints;
};
//=============================================================================

/*
Bfs algorithm from 2 nodes
*/
//=============================================================================
std::vector<sf::Vector2f> Bfs::BFS(Node* from, Node* to)
{

	std::vector< Node*> open_list;

	//adds father first
	open_list.push_back(from);

	//colors grey
	from->set_color(Color::Grey);

	//sets null
	from->set_father(nullptr);

	Node* head_of_list;
	while (1)
	{
		//for protection
		if (open_list.size() == 0)
			return get_path(nullptr);

		//getting the first variable from open list
		head_of_list = open_list[0];

		if (check_reached(head_of_list,to))
			break;
		//adds neighbors if they arent colored
		//colors them 
		//colors myself in black
		//delets myself from the list
		handle_curr(head_of_list,open_list);
		open_list.erase(open_list.begin());

	}
	return get_path(head_of_list);
}
//=============================================================================

//=============================================================================
void Bfs::set_father(Node* node, Node* father)
{
	node->set_father(father);
}
//=============================================================================

//=============================================================================
bool Bfs::check_reached(Node* curr, Node * to)
{
	if (curr == to)
		return true;

	return false;

}
//=============================================================================

//=============================================================================
void Bfs::handle_curr(Node * curr, std::vector< Node*> & open_list)
{
	//from grey to black
	curr->set_color();
	std::vector<Node* > neigbors = curr->get_neighbor_list();

	for (int i = 0; i < neigbors.size(); ++i)
	{
		//if we dont want them we delete
		if (neigbors[i]->get_color() == Color::White)
		{
			neigbors[i]->set_color();
			neigbors[i]->set_father(curr);
			open_list.push_back(neigbors[i]);
		}
	}
}
//=============================================================================

//=============================================================================
std::vector<sf::Vector2f> Bfs::get_path(Node * last)
{
	std::vector<sf::Vector2f> waypoints;

	//for protection
	if (last == nullptr)
	{
		waypoints.push_back(sf::Vector2f(-1, -1));
		return waypoints;
	}

	
	while (last->get_father() != nullptr)
	{
		waypoints.insert(waypoints.begin(), last->get_location());
		last = last->get_father();
	}

	return waypoints;
}
//=============================================================================

