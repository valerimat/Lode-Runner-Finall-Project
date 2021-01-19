#pragma once
#include "Algo.h"
#include <SFML/Graphics.hpp>
class Node;
class Graph;


class Bfs :public Algo
{
public:
	//Main call function:
	std::vector<sf::Vector2f> CalcPath(Graph& graph, sf::Vector2f our_location, sf::Vector2f wanted_location) override;
private:

	std::vector<sf::Vector2f> bfs(Node * from , Node * to);
	void SetFather(Node* node, Node* father);
	bool check_if_reached(Node* curr, Node* to);
	void handle_curr(Node* curr, std::vector< Node*>& open_list);
	std::vector<sf::Vector2f> get_path(Node* last);
	
};