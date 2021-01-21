#pragma	once
#include <SFML/Graphics.hpp>
#include "Macros.h"

class Node
{
public:
	Node(sf::Vector2f location);
	void set_father(Node* father);
	//do we really need weight???
	//void set_weight(int weight);
	void set_color();
	void set_color(Color color);

	void reset_color();
	void set_left_neighbor(Node* node);
	void set_right_neighbor(Node* node);
	void set_top_neigbor(Node* node);
	void set_bot_neighbor(Node* node);

	Node* get_left();
	Node* get_right();
	Node* get_top();
	Node* get_bot();

	Node* get_random_neighbor(int radom);
	std::vector<Node*> get_neighbor_list();
	void reset();
	//getters:
	Color get_color();
	//get father:
	Node* get_father();
	//get location:
	sf::Vector2f get_location();
	void print_node();
	sf::Vector2f get_location_x_y();

private:
	//setting default values for security
	//for bfs usage only:
	Color m_color = Color ::White;
	Node* m_father = nullptr;
	int m_weight = 0;

	sf::Vector2f m_location;

	//array of neigbors:
	std::vector<Node*> neig_arr;

	//neighboors: 
	Node* right_n = nullptr;
	Node* left_n = nullptr;
	Node* top_n = nullptr;
	Node* bottom_n= nullptr;
};