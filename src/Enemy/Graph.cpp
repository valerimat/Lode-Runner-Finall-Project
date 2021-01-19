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
		AddRow(matrix, m_map, curr_row , width);
		curr_row--;
	}

	Clenup(matrix);
	CreateNodeMatrix(matrix);
	LinkNeighborsToList(matrix);
}
//-----------------------------------------------------------------------------

//function that runs on rows and fills up matrix
void Graph::AddRow(std::vector<std::vector<int>> & matrix, std::vector<std::string> m_map, int row,int width)
{
	for (int i = 0; i < width; i++)
	{
		if (WeFoundGround(m_map, i, row) && !WeFoundLadder(m_map, i, row))
			matrix[row][i] = PLATFROM_INT;
		else if(WeFoundRope(m_map, i, row))
			matrix[row][i] = ROPE_INT;
		else if (WeFoundLadder(m_map, i, row))
			matrix[row][i] = LADDER_INT;
		else if (WeFoundPlayer(m_map, i, row))
			matrix[row][i] = PLATFROM_INT;
		else if(WeFoundPlayer(m_map, i, row) || WeFoundAir(m_map, i, row))
			matrix[row][i] = AIR_INT;
		else
			matrix[row][i] = GROUND_INT;
	}
	
}
//-----------------------------------------------------------------------------

//that uses:
//==============Found Functions:
bool Graph::WeFoundGround(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] != GROUND && m_map[row + 1][i] == GROUND)
		return true;
	else if (m_map[row][i] != GROUND && m_map[row + 1][i] == LADDER && m_map[row][i] != LADDER)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::WeFoundLadder(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == LADDER)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::WeFoundPlayer(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == PLAYER)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::WeFoundEnemy(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == ENEMY)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::WeFoundRope(std::vector<std::string> m_map, int i, int row)
{
	if (m_map[row][i] == POLE)
		return true;

	return false;
}
//-----------------------------------------------------------------------------

bool Graph::WeFoundAir(std::vector<std::string> m_map, int i, int row)
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
void Graph::CreateNodeMatrix(std::vector<std::vector<int>> matrix)
{
	SetMatriciesSizes(matrix.size(), matrix[0].size());

	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] != GROUND_INT)
			{
				Node* new_node = new Node(sf::Vector2f(j * MacroSettings::GetSettings().GetScaleWidth() * 50 
					                                 + 0.5 * MacroSettings::GetSettings().GetScaleWidth() * 50,
					                                     i * MacroSettings::GetSettings().GetScaleWidth() * 50
													+ 0.5 * MacroSettings::GetSettings().GetScaleWidth() * 50 + 50));
				node_matrix[i][j] = new_node;
			}
			else
				node_matrix[i][j] = nullptr;
		}
	}
}
//-----------------------------------------------------------------------------

//that uses:
void Graph::SetMatriciesSizes(int height, int width)
{
	node_matrix.resize(height);
	for (int i = 0; i < node_matrix.size(); ++i)
	{
		node_matrix[i].resize(width);
	}
}
//-----------------------------------------------------------------------------

//then we link neighboors together:
void Graph::LinkNeighborsToList(std::vector<std::vector<int>> matrix)
{
	for (int i = 0; i < node_matrix.size(); ++i)
	{
		for (int j = 0; j < node_matrix[i].size(); ++j)
		{
			if (node_matrix[i][j])
			{
				SetNeighbors(i, j, matrix, node_matrix[i][j]);

				neighbor_list.push_back(node_matrix[i][j]);
			}
		}
	}
}
//-----------------------------------------------------------------------------

//for this we use this set:
void Graph::SetNeighbors(int i, int j, std::vector<std::vector<int>> matrix, Node* node)
{
	node->SetTop(AboveNeighbor(i, j, matrix));
	node->SetBot(BellowNeighbor(i, j, matrix));
	node->SetLeft(LeftNeighbor(i, j, matrix));
	node->SetRight(RightNeighbor(i, j, matrix));
}
//-----------------------------------------------------------------------------

//that uses:
//==============Linking Neighbors:
Node* Graph::AboveNeighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if (i - 1 >= 0)
	{
		if (matrix[i][j] == LADDER_INT && matrix[i - 1][j] != GROUND_INT)
			return node_matrix[i - 1][j];
	}

	return nullptr;
}
//-----------------------------------------------------------------------------

Node* Graph::BellowNeighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if (i + 1 < matrix[0].size())
	{
		if (matrix[i + 1][j] != GROUND_INT)
			return node_matrix[i + 1][j];
	}

	return nullptr;
}
//-----------------------------------------------------------------------------

Node* Graph::LeftNeighbor(int i, int  j, std::vector<std::vector<int>> matrix)
{
	if (j - 1 > 0)
	{
		if (matrix[i][j] != AIR_INT && matrix[i][j - 1] != GROUND_INT)
			return node_matrix[i][j - 1];
	}
	return nullptr;
}
//-----------------------------------------------------------------------------

Node* Graph::RightNeighbor(int i, int  j, std::vector<std::vector<int>> matrix)
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
Node * Graph::GetClosestNode(sf::Vector2f & location)
{
	//thats our center
	float x = location.x + 0.5f * MacroSettings::GetSettings().GetScaleWidth() * 50; ;
	float y = location.y + 0.5f * MacroSettings::GetSettings().GetScaleWidth() * 50; ;

	//we will find the left and the right posibilitys by rouding up
	x = x / (MacroSettings::GetSettings().GetScaleWidth() * 50);
	y = (y - 50) / (MacroSettings::GetSettings().GetScaleWidth() * 50);

	//now we round up
	round(x);
	round(y);

	Node* node = GetNode(y,x);

	return node;
	
}
//-----------------------------------------------------------------------------

//get node that is found in the matrix in x,y
Node* Graph::GetNode(int x, int y)
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
