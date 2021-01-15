#include "Node.h"
#include <iostream>

Node::Node(sf::Vector2f location):
	m_location(location)
{}

void Node::set_father(Node* father)
{
	m_father = father;
}
//do we really need weight???
//void set_weight(int weight);
void Node::set_color()
{
	switch (m_color)
	{
	case Color::White:
		m_color = Color::Grey;
		break;
	case Color::Grey:
		m_color = Color::Black;
		break;
	case Color::Black:
		//do nothing
		break;
	default:
		break;
	}
}
void Node::reset_color()
{
	m_color = Color::White;
}

void Node::set_left(Node* node)
{
	if (node != nullptr)
		neig_arr.push_back(node);

	left_n = node;
}
void Node::set_right(Node* node)
{
	right_n = node;
	if (node != nullptr)
		neig_arr.push_back(node);
}

void Node::set_top(Node* node)
{
	top_n = node;
	if (node != nullptr)
		neig_arr.push_back(node);
}

void Node::set_bot(Node* node)
{
	bottom_n = node;
	if (node != nullptr)
		neig_arr.push_back(node);
}

Node* Node::get_random_neigbor(int random)
{
	random = random % neig_arr.size();

	return neig_arr[random];
}

Node* Node::get_left()
{
	return left_n;
}
Node* Node::get_right()
{
	return right_n;
}

Node* Node::get_top()
{
	return top_n ;
}

Node* Node::get_bot()
{
	return bottom_n ;
}

//getters:
Color Node::get_color()
{
	return m_color;
}
//get father:
Node* Node::get_father()
{
	return m_father;
}
//get location:
sf::Vector2f Node::get_location()
{
	return m_location;
}

void Node::reset()
{
	set_color(Color::White);
	set_father(nullptr);
}

void Node::print_node()
{
	std::cout << "(" << m_location.x << "," << m_location.y << ") ";

	if(top_n)
		std::cout << "(" << top_n->get_location().x << "," << top_n->get_location().y << ") ";
	if(bottom_n)
		std::cout << "(" << bottom_n->get_location().x << "," << bottom_n->get_location().y << ") ";
	if(left_n)
		std::cout << "(" << left_n->get_location().x << "," << left_n->get_location().y << ") ";
	if(right_n)
		std::cout << "(" << right_n->get_location().x << "," << right_n->get_location().y << ") ";

	std::cout << std::endl;

}

std::vector<Node*> Node::get_neigbor_list()
{
	return neig_arr;
}
void Node::set_color(Color color)
{
	m_color = color;
}
