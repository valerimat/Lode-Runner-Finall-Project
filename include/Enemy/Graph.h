#pragma once
#include<vector>
#include<string>
#include <SFML/Graphics.hpp>
class Node;

class Graph
{
public:

	//C-tor
	Graph(std::vector<std::string> map,int width, int height);
	
	//For algorithms:
	Node* get_closest_node(sf::Vector2f& location);
	void Clean();

	sf::Vector2f get_free_location();
	//For debug:
	void Draw(sf::RenderWindow& window);
	
private:

	//Functions used in the graph creation
	void set_matricies_sizes(int height, int width);
	void create_node_matrix(std::vector<std::vector<int>> matrix);
	void link_neighbors_to_list(std::vector<std::vector<int>> matrix);
	void set_neighbors(int i, int j,std::vector<std::vector<int>> matrix, Node* node);
	Node* get_node(int x, int y);

	Node* above_neighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	Node* bellow_neighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	Node* left_neighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	Node* right_neighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	
	void add_row(std::vector<std::vector<int>> & m_nodes, std::vector<std::string> m_map, int row, int width);
	void Clenup(std::vector<std::vector<int>>& matrix);
	
	bool found_ground(std::vector<std::string>  m_map, int i, int row);
	bool found_ladder(std::vector<std::string> m_map, int i, int row);
	bool found_player(std::vector<std::string> m_map, int i, int row);
	bool found_rope(std::vector<std::string> m_map, int i, int row);
	bool found_enemy(std::vector<std::string> m_map, int i, int row);
	bool found_air(std::vector<std::string> m_map, int i, int row);
	

	bool only_bottom_neighboor(Node * node);

	//Members
	std::vector<Node*> neighbor_list;
	std::vector<std::vector<Node*>> node_matrix;
};