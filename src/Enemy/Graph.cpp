#include "Graph.h"
#include "Macros.h"
#include "Node.h"
#include "MacroSettings.h"
#include <iostream>
#include <math.h>

//=============================================CREATION==================================================
//=======================================================================================================
//main creating function:
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

	Clenup(matrix);
	create_node_matrix(matrix);
	link_neighbors_to_list(matrix);
}
//-----------------------------------------------------------------------------

//function that runs on rows and fills up matrix
void Graph::add_row(std::vector<std::vector<int>> & matrix, std::vector<std::string> m_map, int row,int width)
{
	for (int i = 0; i < width; i++)
	{
		if (found_ground(m_map, i, row) && !found_ladder(m_map, i, row))
			matrix[row][i] = PLATFROM_INT;
		else if(found_rope(m_map, i, row))
			matrix[row][i] = ROPE_INT;
		else if (found_ladder(m_map, i, row))
			matrix[row][i] = LADDER_INT;
		else if (found_player(m_map, i, row))
			matrix[row][i] = PLATFROM_INT;
		else if(found_player(m_map, i, row) || found_air(m_map, i, row))
			matrix[row][i] = AIR_INT;
		else
			matrix[row][i] = GROUND_INT;
	}
	
}
//-----------------------------------------------------------------------------

//that uses:
//==============Found Functions:
bool Graph::found_ground(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] != GROUND && m_map[row + 1][i] == GROUND)
		return true;
	else if (m_map[row][i] != GROUND && m_map[row + 1][i] == LADDER && m_map[row][i] != LADDER)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::found_ladder(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == LADDER)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::found_player(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == PLAYER)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::found_enemy(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == ENEMY)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::found_rope(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == POLE)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::found_air(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == NONE)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

//then we clen it with :
//THIS FUNC ALITTLE BIT MESSY MIGHT WANNA FIX
void Graph::Clenup(std::vector<std::vector<int>>& matrix)
{
	//we want to run on columns and not on rows
	int width = matrix[0].size();

	for (int col = 0; col < width; ++col)
	{
		for (int row = 0; row < matrix.size() - 1; ++row)//we dont want last row (also for safety reasons)
		{
			if (matrix[row][col] == GROUND_INT) //if we found a platform / ground
			{
				if (matrix[row + 1][col] == AIR_INT)//and therer is air bellow
					++row;
				else
					continue;

				//if we didnt continue
				while (matrix[row][col] == AIR_INT)
				{

					//for safety:
					if (row > matrix.size())
						break;

					if (col > 0)
						if (matrix[row][col - 1] == LADDER_INT || matrix[row][col - 1] == PLATFROM_INT)
						{
							row++;
							break;
						}

					if (row + 1 < width)
						if (matrix[row][col + 1] == LADDER_INT || matrix[row][col + 1] == PLATFROM_INT)
						{
							++row;
							break;
						}


					matrix[row][col] = GROUND_INT; // we mark it as ground;
					++row;
				}
			}
		}
	}
} 
//-----------------------------------------------------------------------------

//then we create node matrix:
void Graph::create_node_matrix(std::vector<std::vector<int>> matrix)
{
	set_matricies_sizes(matrix.size(), matrix[0].size());

	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] != GROUND_INT)
			{
				Node* new_node = new Node(sf::Vector2f(j * MacroSettings::get_settings().get_size_of_tile()
					                                 + 0.5 * MacroSettings::get_settings().get_size_of_tile(),
					                                     i * MacroSettings::get_settings().get_size_of_tile()
													+ 0.5 * MacroSettings::get_settings().get_size_of_tile() + 50));
				node_matrix[i][j] = new_node;
			}
			else
				node_matrix[i][j] = nullptr;
		}
	}
}
//-----------------------------------------------------------------------------

//that uses:
void Graph::set_matricies_sizes(int height, int width)
{
	node_matrix.resize(height);
	for (int i = 0; i < node_matrix.size(); ++i)
	{
		node_matrix[i].resize(width);
	}
}
//-----------------------------------------------------------------------------

//then we link neighboors together:
void Graph::link_neighbors_to_list(std::vector<std::vector<int>> matrix)
{
	for (int i = 0; i < node_matrix.size(); ++i)
	{
		for (int j = 0; j < node_matrix[i].size(); ++j)
		{
			if (node_matrix[i][j])
			{
				set_neighbors(i, j, matrix, node_matrix[i][j]);

				neighbor_list.push_back(node_matrix[i][j]);
			}
		}
	}
}
//-----------------------------------------------------------------------------

//for this we use this set:
void Graph::set_neighbors(int i, int j, std::vector<std::vector<int>> matrix, Node* node)
{
	node->SetTop(above_neighbor(i, j, matrix));
	node->SetBot(bellow_neighbor(i, j, matrix));
	node->SetLeft(left_neighbor(i, j, matrix));
	node->SetRight(right_neighbor(i, j, matrix));
}
//-----------------------------------------------------------------------------

//that uses:
//==============Linking Neighbors:
Node* Graph::above_neighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if (i - 1 >= 0)
	{
		if (matrix[i][j] == LADDER_INT && matrix[i - 1][j] != GROUND_INT)
			return node_matrix[i - 1][j];
	}

	return nullptr;
}
//-----------------------------------------------------------------------------

Node* Graph::bellow_neighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if (i + 1 < matrix[0].size())
	{
		if (matrix[i + 1][j] != GROUND_INT)
			return node_matrix[i + 1][j];
	}

	return nullptr;
}
//-----------------------------------------------------------------------------

Node* Graph::left_neighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if (j - 1 > 0)
	{
		if (matrix[i][j] != AIR_INT && matrix[i][j - 1] != GROUND_INT)
			return node_matrix[i][j - 1];
	}
	return nullptr;
}
//-----------------------------------------------------------------------------

Node* Graph::right_neighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if (j + 1 < matrix[0].size())
	{
		if (matrix[i][j] != AIR_INT && matrix[i][j + 1] != GROUND_INT)
			return node_matrix[i][j + 1];
	}

	return nullptr;
}
//=======================================================================================================
//=======================================================================================================

//==========================================For the algorithms===========================================
//=======================================================================================================
//those functions will help our algorithms
//we get the center of ourselfs and check if we fall on a horizonatl edge
//the margin for mistake is <1
//if not we return null ptr
Node * Graph::get_closest_node(sf::Vector2f & location)
{
	//thats our center
	float x = location.x + 0.5f * MacroSettings::get_settings().get_size_of_tile() ;
	float y = location.y + 0.5f * MacroSettings::get_settings().get_size_of_tile();

	//we will find the left and the right posibilitys by rouding up
	x = x / (MacroSettings::get_settings().get_size_of_tile());
	y = (y - 50) / (MacroSettings::get_settings().get_size_of_tile());

	//now we round up
	round(x);
	round(y);

	Node* node = get_node(y,x);

	return node;
	
}
//-----------------------------------------------------------------------------

//get node that is found in the matrix in x,y
Node* Graph::get_node(int x, int y)
{
	return node_matrix[x][y];
}
//-----------------------------------------------------------------------------

//clean graph after bfs
void Graph::Clean()
{
	for (int i = 0; i < neighbor_list.size(); ++i)
		neighbor_list[i]->Reset();
}
//-----------------------------------------------------------------------------

sf::Vector2f Graph::get_free_location()
{
	int height = node_matrix.size();
	int width = node_matrix[0].size();

	int i = rand() % height;
	int j = rand() % width;

	while (1)
	{
		if (node_matrix[i][j] != nullptr)
			if(!only_bottom_neighboor(node_matrix[i][j]))
			break;
		
		i = rand() % height;
		j = rand() % width;
	}
	
	

	return node_matrix[i][j]->get_location_x_y();
}


bool Graph::only_bottom_neighboor (Node * node)
{
	if (node->GetNeighborList().size() == 1)
		if (node->GetBot() != nullptr)
		{
			return true;
		}

	return false;
	
}
//=======================================================================================================
//=======================================================================================================
//_____________________For Dubug DELETE IN PRODUCTION:
void Graph::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < neighbor_list.size(); i++)
	{
		if (neighbor_list[i] == nullptr)
			continue;
		sf::RectangleShape rect;
		rect.setPosition(neighbor_list[i]->get_location());
		rect.setSize(sf::Vector2f(10, 10));
		window.draw(rect);
		
		if (neighbor_list[i]->GetTop() != nullptr)
		{
			sf::RectangleShape rect;
			rect.setPosition(neighbor_list[i]->get_location());
			sf::Vector2f size = neighbor_list[i]->GetTop()->get_location() - neighbor_list[i]->get_location();

			if (size.x == 0)
				size.x = 5;
			if (size.y == 0)
				size.y = 5;

			
			rect.setFillColor(sf::Color::Yellow);
		

			rect.setSize(sf::Vector2f(size));
			window.draw(rect);
		}
		
		if (neighbor_list[i]->GetBot() != nullptr)
		{
			sf::RectangleShape rect;
			rect.setPosition(neighbor_list[i]->get_location());
			sf::Vector2f size = neighbor_list[i]->GetBot()->get_location() - neighbor_list[i]->get_location();

			if (size.x == 0)
				size.x = 5;
			if (size.y == 0)
				size.y = 5;
			rect.setFillColor(sf::Color::Black);
			
			size.x -= 10;


			rect.setSize(sf::Vector2f(size));
			window.draw(rect);
		}

		if (neighbor_list[i]->GetRight() != nullptr)
		{
			sf::RectangleShape rect;
			rect.setPosition(neighbor_list[i]->get_location());
			sf::Vector2f size = neighbor_list[i]->GetRight()->get_location() - neighbor_list[i]->get_location();

			if (size.x == 0)
				size.x = 5;
			if (size.y == 0)
				size.y = 5;

			size.y -= 10;
			rect.setFillColor(sf::Color::Red);
	

			rect.setSize(sf::Vector2f(size));
			window.draw(rect);
		}

		if (neighbor_list[i]->GetLeft() != nullptr)
		{
			sf::RectangleShape rect;
			rect.setPosition(neighbor_list[i]->get_location());
			sf::Vector2f size = neighbor_list[i]->GetLeft()->get_location() - neighbor_list[i]->get_location();

			if (size.x == 0)
				size.x = 5;
			if (size.y == 0)
				size.y = 5;
	
			rect.setFillColor(sf::Color::Green);

			rect.setSize(sf::Vector2f(size));
			window.draw(rect);
		}
	}
}
//-----------------------------------------------------------------------------
