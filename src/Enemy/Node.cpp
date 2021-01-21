#include "Node.h"
#include <iostream>
#include "MacroSettings.h"

// c-tor
Node::Node(sf::Vector2f location):
	m_location(location)
{}
//-----------------------------------------------------------------------------

void Node::set_father(Node* father)
{
	m_father = father;
}
//-----------------------------------------------------------------------------

//do we really need weight???
//void set_weight(int weight);
void Node::SetColor()
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
//-----------------------------------------------------------------------------

void Node::ResetColor()
{
	m_color = Color::White;
}
//-----------------------------------------------------------------------------

void Node::SetLeft(Node* node)
{
	if (node != nullptr)
		neig_arr.push_back(node);

	left_n = node;
}
//-----------------------------------------------------------------------------

void Node::SetRight(Node* node)
{
	right_n = node;
	if (node != nullptr)
		neig_arr.push_back(node);
}
//-----------------------------------------------------------------------------

void Node::SetTop(Node* node)
{
	top_n = node;
	if (node != nullptr)
		neig_arr.push_back(node);
}
//-----------------------------------------------------------------------------

void Node::SetBot(Node* node)
{
	bottom_n = node;
	if (node != nullptr)
		neig_arr.push_back(node);
}
//-----------------------------------------------------------------------------

Node* Node::GetRandomNeighbor(int random)
{
	random = random % neig_arr.size();

	return neig_arr[random];
}
//-----------------------------------------------------------------------------

Node* Node::GetLeft()
{
	return left_n;
}
//-----------------------------------------------------------------------------

Node* Node::GetRight()
{
	return right_n;
}
//-----------------------------------------------------------------------------

Node* Node::GetTop()
{
	return top_n ;
}
//-----------------------------------------------------------------------------

Node* Node::GetBot()
{
	return bottom_n ;
}
//-----------------------------------------------------------------------------

//getters:
Color Node::GetColor()
{
	return m_color;
}
//-----------------------------------------------------------------------------

//gets father
Node* Node::GetFather()
{
	return m_father;
}
//-----------------------------------------------------------------------------

//gets location
sf::Vector2f Node::get_location()
{
	return m_location;
}
//-----------------------------------------------------------------------------

void Node::Reset()
{
	SetColor(Color::White);
	set_father(nullptr);
}
//-----------------------------------------------------------------------------

void Node::PrintNode()
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
//-----------------------------------------------------------------------------

std::vector<Node*> Node::GetNeighborList()
{
	return neig_arr;
}
//-----------------------------------------------------------------------------

void Node::SetColor(Color color)
{
	m_color = color;
}
//-----------------------------------------------------------------------------

sf::Vector2f Node::get_location_x_y()
{
	auto size_of_tile = MacroSettings::get_settings().get_size_of_tile();

	float x = get_location().x - 0.5f * size_of_tile;
	float y = get_location().y - 0.5f * size_of_tile - 50.f;

	x /= size_of_tile;
	y /= size_of_tile;

	return sf::Vector2f(x, y);

}
