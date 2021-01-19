#include "Bfs.h"
#include "Graph.h"
#include "Node.h"
#include <iostream>

std::vector<sf::Vector2f> Bfs::CalcPath(Graph& graph, sf::Vector2f our_location, sf::Vector2f wanted_location)
{
	std::vector<sf::Vector2f> waypoints;
	Node* from, * to;

	from =  graph.GetClosestNode(our_location);

	if (from == nullptr)
	{
		waypoints.push_back(our_location);
		return waypoints;
	}

	to = graph.GetClosestNode(wanted_location);
	if (to == nullptr)
	{
		sf::Vector2f off(0, -SIZE_OF_TILE);
		wanted_location += off;
		to = graph.GetClosestNode((wanted_location));
	}

	waypoints = BFS(from, to);

	graph.Clean();

	return waypoints;
};
//-----------------------------------------------------------------------------

/*
Bfs algorithm from 2 nodes
*/
std::vector<sf::Vector2f> Bfs::BFS(Node* from, Node* to)
{

	std::vector< Node*> open_list;

	//adds father first
	open_list.push_back(from);

	//colors grey
	from->SetColor(Color::Grey);

	//sets null
	from->SetFather(nullptr);

	Node* head_of_list;
	while (1)
	{
		//for protection
		if (open_list.size() == 0)
			return GetPath(nullptr);

		//getting the first variable from open list
		head_of_list = open_list[0];

		if (CheckIfReached(head_of_list,to))
			break;
		//adds neighbors if they arent colored
		//colors them 
		//colors myself in black
		//delets myself from the list
		HandleCurr(head_of_list,open_list);
		open_list.erase(open_list.begin());

	}
	return GetPath(head_of_list);
}
//-----------------------------------------------------------------------------

void Bfs::SetFather(Node* node, Node* father)
{
	node->SetFather(father);
}
//-----------------------------------------------------------------------------

bool Bfs::CheckIfReached(Node* curr, Node * to)
{
	if (curr == to)
		return true;

	return false;

}
//-----------------------------------------------------------------------------

void Bfs::HandleCurr(Node * curr, std::vector< Node*> & open_list)
{
	//from grey to black
	curr->SetColor();
	std::vector<Node* > neigbors = curr->GetNeighborList();

	for (int i = 0; i < neigbors.size(); ++i)
	{
		//if we dont want them we delete
		if (neigbors[i]->GetColor() == Color::White)
		{
			neigbors[i]->SetColor();
			neigbors[i]->SetFather(curr);
			open_list.push_back(neigbors[i]);
		}
	}
}
//-----------------------------------------------------------------------------

std::vector<sf::Vector2f> Bfs::GetPath(Node * last)
{
	std::vector<sf::Vector2f> waypoints;

	//for protection
	if (last == nullptr)
	{
		waypoints.push_back(sf::Vector2f(-1, -1));
		return waypoints;
	}

	
	while (last->GetFather() != nullptr)
	{
		waypoints.insert(waypoints.begin(), last->get_location());
		last = last->GetFather();
	}

	return waypoints;
}
//-----------------------------------------------------------------------------

