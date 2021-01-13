#include "Graph.h"
#include "Macros.h"
#include <iostream>
//#include "GraphNode.h"

Graph::Graph(std::vector<std::string> m_map,int width, int height)
{
	//first we create a 2 d vector of graph nodes represented by x,y (theyr center);
	std::vector<std::vector<int>> matrix(height);
	for (int i =0; i <matrix.size(); ++i)
	{
		matrix[i].resize(width);
	}

	int lowest_row = matrix.size()-1;//always the most bottom row will be floor

	int curr_row = lowest_row;

	while (curr_row >= 0)
	{
		add_row(matrix, m_map, curr_row , width);
		curr_row--;
	}
	for (auto vec : matrix)
	{
		for (int m : vec)
		{
			if(m == 0)
				std::cout << ' ';
			else
			std::cout << m;
		}
		std::cout << std::endl;
	}
	std::cout << "+++++++++++++++++++++++++" << std::endl;

	//clenup(matrix);
	create_neighbor_list(matrix);
	for (auto a : neighbor_list)
	{
		for (sf::Vector2f vec : a)
		{
			std::cout << "(" << vec.x << " " << vec.y << ")" << " ";
		}
		std::cout << std::endl;
	}
	
	
}


void Graph::add_row(std::vector<std::vector<int>> & matrix, std::vector<std::string> m_map, int row,int width)
{
	for (int i = 0; i < width; i++)
	{
		if (we_found_ground(m_map, i, row) && !we_found_ladder(m_map, i, row))
			matrix[row][i] = PLATFROM_INT;
		else if(we_found_rope(m_map, i, row))
			matrix[row][i] = ROPE_INT;
		else if (we_found_ladder(m_map, i, row))
			matrix[row][i] = LADDER_INT;
		else if (we_found_player(m_map, i, row))
			matrix[row][i] = PLATFROM_INT;
		else if(we_found_player(m_map, i, row))
			matrix[row][i] = AIR_INT;
		else
			matrix[row][i] = GROUND_INT;
	}
	
}
bool Graph::vertical_edge(int i, int j)
{
	sf::Vector2f parent = neighbor_list[i][0];
	sf::Vector2f neigh = neighbor_list[i][j];
	if (abs(parent.y - neigh.y) > 0)
		return true;

	return false;
}
void Graph::clenup(std::vector<std::vector<int>> & matrix)
{
	
}

sf::Vector2f Graph::get_parent_node(int index)
{
	return neighbor_list[index][0];
}
sf::Vector2f Graph::get_neighboor_node(int i, int j)
{
	return neighbor_list[i][j];
}

sf::Vector2f Graph::we_are_on_edge_hori(sf::FloatRect& rect)
{
	sf::RectangleShape line_rect;
		line_rect.setSize(sf::Vector2f(1, 1));

	for (int i = 0; i < neighbor_list.size(); ++i)
	{
		line_rect.setPosition(neighbor_list[i][0]);

		for (int j = 1; j < neighbor_list[i].size(); j++)
		{
			sf::Vector2f offset = neighbor_list[i][j] - neighbor_list[i][0];
			offset.x = abs(offset.x);
			offset.y = abs(offset.y);
			line_rect.setSize(offset + sf::Vector2f(1,1));

			if (line_rect.getGlobalBounds().intersects(rect))
				if(!vertical_edge(i,j))
				return sf::Vector2f(i, j);
		}
	}
	return sf::Vector2f(-1, -1);
}




void Graph::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < neighbor_list.size(); i++)
	{
		sf::RectangleShape rect;
		rect.setPosition(neighbor_list[i][0]);
		rect.setSize(sf::Vector2f(10, 10));
		window.draw(rect);
		for (int j = 1; j < neighbor_list[i].size(); ++j)
		{
			sf::RectangleShape rect;
			rect.setPosition(neighbor_list[i][0]);
			sf::Vector2f size = neighbor_list[i][j]-  neighbor_list[i][0]  ;
			if (size.x == 0)
				size.x = 5;
			if (size.y == 0)
				size.y = 5;

			if (size.x > 0 && size.x!=5)
			{
				rect.setFillColor(sf::Color::Red);
				size.y -= 10;
			}
			else if (size.x < 0)
				rect.setFillColor(sf::Color::Green);
			else if (size.y < 0)
			{
				rect.setFillColor(sf::Color::Black);
				size.x -= 10;
			}
			else if (size.y > 0 && size.y !=5)
				rect.setFillColor(sf::Color::Yellow);


			rect.setSize(sf::Vector2f(size));
			window.draw(rect);
		}

	}
}
//can make it to 1 func
sf::Vector2f Graph::we_are_on_edge(sf::FloatRect& rect)
{
	sf::RectangleShape line_rect;
	line_rect.setSize(sf::Vector2f(1, 1));

	for (int i = 0; i < neighbor_list.size(); ++i)
	{
		line_rect.setPosition(neighbor_list[i][0]);

		for (int j = 1; j < neighbor_list[i].size(); j++)
		{
			sf::Vector2f offset = neighbor_list[i][j] - neighbor_list[i][0];
			offset.x = abs(offset.x);
			offset.y = abs(offset.y);
			line_rect.setSize(offset + sf::Vector2f(1, 1));

			if (line_rect.getGlobalBounds().intersects(rect))
					return sf::Vector2f(i, j);
		}
	}
	return sf::Vector2f(-1, -1);
}

void Graph::create_neighbor_list(std::vector<std::vector<int>> matrix)
{
	for(int i = 0; i < matrix.size() ;++i)
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] != GROUND_INT)
			{
				//we add ourself to our list
				sf::Vector2f our_center(j * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE, i * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE + 50);
				std::vector<sf::Vector2f> our_list;
				our_list.push_back(our_center);
				find_neighbors(matrix, our_list, i, j);		
				neighbor_list.push_back(our_list);
			}
		}
}
int Graph::we_are_on_node(sf::FloatRect& rect)
{
	for (int i =0; i < neighbor_list.size() ; ++i)
	{
		if (rect.contains(neighbor_list[i][0]))
			return i;
	}
	return -1;
}

sf::Vector2f Graph::get_random_neighboor(int i, int rnd)
{
	int size = neighbor_list[i].size();

	rnd = rnd % size;
	if (rnd == 0)
		rnd = 1;

	return neighbor_list[i][rnd];
}
void Graph::find_neighbors(std::vector<std::vector<int>> matrix, std::vector<sf::Vector2f> &our_list,int i, int j)
{
	//above
	sf::Vector2f top_node = above_neighbor(i, j, matrix);
	sf::Vector2f bottom_node = bellow_neighbor(i, j, matrix);
	sf::Vector2f lef_node = left_neighbor(i, j, matrix);
	sf::Vector2f right_node = right_neighbor(i, j, matrix);

	if (top_node != sf::Vector2f(0,0))
		our_list.push_back(top_node);
	if (bottom_node!= sf::Vector2f(0,0))
		our_list.push_back(bottom_node);
	if (lef_node != sf::Vector2f(0, 0))
		our_list.push_back(lef_node);
	if (right_node != sf::Vector2f(0, 0))
		our_list.push_back(right_node);
}

sf::Vector2f Graph::above_neighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if(matrix[i][j] == LADDER_INT && matrix[i-1][j]!=ROPE_INT && matrix[i - 1][j] != GROUND_INT)
		return sf::Vector2f(j * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE, (i - 1) * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE + 50);
	
	return sf::Vector2f(0, 0);
}
sf::Vector2f Graph::bellow_neighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if(matrix[i+1][j] != GROUND_INT )
		return sf::Vector2f(j * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE, (i + 1) * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE + 50);

	return sf::Vector2f(0, 0);
}
sf::Vector2f Graph::left_neighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if (matrix[i][j] != AIR_INT && matrix[i][j-1] != GROUND_INT)
		return sf::Vector2f ((j-1) * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE, i * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE + 50);

	return sf::Vector2f(0, 0);
}
sf::Vector2f Graph::right_neighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{

	if (matrix[i][j] != AIR_INT && matrix[i][j + 1] != GROUND_INT)
		return sf::Vector2f((j + 1)* SIZE_OF_TILE + 0.5 * SIZE_OF_TILE, i * SIZE_OF_TILE + 0.5 * SIZE_OF_TILE + 50);

	return sf::Vector2f(0, 0);
}
//==============Found Functions:
bool Graph::we_found_ground(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] != GROUND && m_map[row + 1][i] == GROUND)
		return true;
	else if (m_map[row][i] != GROUND && m_map[row + 1][i] == LADDER && m_map[row][i] != LADDER)
		return true;

	return false;
}
bool Graph::we_found_ladder(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == LADDER)
		return true;
	
	return false;
}
bool Graph::we_found_player(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == PLAYER)
		return true;

	return false;
}
bool Graph::we_found_enemy(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == ENEMY)
		return true;

	return false;
}
bool Graph::we_found_rope(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == POLE)
		return true;

	return false;
}
bool Graph::we_found_air(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == NONE)
		return true;

	return false;
}

int Graph::find_our_index (sf::Vector2f location)
{
	for (int i = 0; i < neighbor_list.size(); i++)
	{
		if (location == neighbor_list[i][0])
			return i;
	}
	return -1;
}

sf::Vector2f Graph::get_max_right_node(int index)
{
	if (index == -1)
		return sf::Vector2f(-1, -1);

	sf::Vector2f our_node = neighbor_list[index][0];
	sf::Vector2f right;
	for (int i = 1; i < neighbor_list[index].size(); i++)
	{
		if (our_node.x < neighbor_list[index][i].x)
			return get_max_right_node(find_our_index(neighbor_list[index][i]));
	}
	return neighbor_list[index][0];

}

sf::Vector2f Graph::get_max_left_node(int index)
{
	if (index == -1)
		return sf::Vector2f(-1, -1);

	sf::Vector2f our_node = neighbor_list[index][0];
	sf::Vector2f right;
	for (int i = 1; i < neighbor_list[index].size(); i++)
	{
		if (our_node.x > neighbor_list[index][i].x)
			return get_max_left_node(find_our_index(neighbor_list[index][i]));
	}
	return neighbor_list[index][0];
}