#pragma once
//======include section======
#include <SFML/Graphics.hpp>
#include "Macros.h"

// Will store tiles for alphaStar algorithm
class Tile
{
public:

	// c-tors
	Tile(sf::Vector2f location,int index_of_father, NextStep move, int h_value);
	Tile();

	// operator functions
	bool operator==(Tile& tile) const;
	bool operator!=(Tile& tile) const;

	// members
	float m_size = SIZE_OF_TILE;
	int f_value;
	int g_value;
	int h_value;
	int m_father;
	NextStep m_move;
	sf::Vector2f m_location;
};




