#pragma	once
#include <SFML/Graphics.hpp>

class Node
{
public:
	Node(sf::Vector2f& location);
	void setup_neighboors(Node* left, Node *right, Node *up, Node* bottom);

private:
	sf::Vector2f m_location;
	Node * m_right = nullptr;
	Node * m_left = nullptr;
	Node * m_up = nullptr;
	Node * m_down = nullptr;
};