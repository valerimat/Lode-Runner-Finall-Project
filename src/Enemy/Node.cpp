#include "Node.h"


Node::Node(sf::Vector2f& location):
	m_location(location)
{}

void Node::setup_neighboors(Node* left, Node* right, Node* up, Node* bottom)
{
	m_right = right;
	m_left = left;
	m_up = up;
	m_down = bottom;

}