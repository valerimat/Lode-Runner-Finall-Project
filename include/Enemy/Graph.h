#pragma once
#include<vector>
#include<string>
#include <SFML/Graphics.hpp>

class Graph
{
public:
	Graph(std::vector<std::string> map,int width, int height);
	sf::Vector2f we_are_on_edge_hori(sf::FloatRect& rect);
	sf::Vector2f we_are_on_edge(sf::FloatRect& rect);
	int we_are_on_node(sf::FloatRect& rect);
	sf::Vector2f get_parent_node(int index);
	sf::Vector2f get_neighboor_node(int i, int j);
	bool vertical_edge(int i, int j);
	sf::Vector2f get_random_neighboor(int i,int rnd);
	sf::Vector2f get_max_right_node(int index);
	sf::Vector2f get_max_left_node(int index);
	int find_our_index(sf::Vector2f location);
	void Draw(sf::RenderWindow& window);
private:

	void find_neighbors(std::vector<std::vector<int>> matrix, std::vector<sf::Vector2f> & our_list,int i ,int j);
	sf::Vector2f above_neighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	sf::Vector2f bellow_neighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	sf::Vector2f left_neighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	sf::Vector2f right_neighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	void create_neighbor_list(std::vector<std::vector<int>> matrix);

	void add_row(std::vector<std::vector<int>> & m_nodes, std::vector<std::string> m_map, int row, int width);
	void clenup(std::vector<std::vector<int>>& matrix);
	
	bool we_found_ground(std::vector<std::string>  m_map, int i, int row);
	bool we_found_ladder(std::vector<std::string> m_map, int i, int row);
	bool we_found_player(std::vector<std::string> m_map, int i, int row);
	bool we_found_rope(std::vector<std::string> m_map, int i, int row);
	bool we_found_enemy(std::vector<std::string> m_map, int i, int row);
	bool we_found_air(std::vector<std::string> m_map, int i, int row);
	

	std::vector<std::vector<sf::Vector2f>> neighbor_list;
};