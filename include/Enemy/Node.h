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
	void SetColor();
	void SetColor(Color color);

	void ResetColor();
	void SetLeft(Node* node);
	void SetRight(Node* node);
	void SetTop(Node* node);
	void SetBot(Node* node);

	Node* GetLeft();
	Node* GetRight();
	Node* GetTop();
	Node* GetBot();

	Node* GetRandomNeighbor(int radom);
	std::vector<Node*> GetNeighborList();
	void Reset();
	//getters:
	Color GetColor();
	//get father:
	Node* GetFather();
	//get location:
	sf::Vector2f get_location();
	void PrintNode();
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