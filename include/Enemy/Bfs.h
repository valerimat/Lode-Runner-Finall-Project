#pragma once
#include "Algo.h"
#include <SFML/Graphics.hpp>
class Node;
class Graph;


class Bfs :public Algo
{
public:
	// main call function:
	std::vector<sf::Vector2f> calc_path(Graph& graph, sf::Vector2f our_location, sf::Vector2f wanted_location) override;
private:

	// private functions
	std::vector<sf::Vector2f> BFS(Node * from , Node * to);
	void set_father(Node* node, Node* father);
	bool check_reached(Node* curr, Node* to);
	void handle_curr(Node* curr, std::vector< Node*>& open_list);
	std::vector<sf::Vector2f> get_path(Node* last);
	
};