#pragma once
#include<vector>
#include<string>
#include <SFML/Graphics.hpp>
class Node;

class Graph
{
public:

	//C-tor
	Graph(std::vector<std::string> map,int width, int height);
	
	//For algorithms:
	Node* GetClosestNode(sf::Vector2f& location);
	void Clean();

	//For debug:
	void Draw(sf::RenderWindow& window);
	
private:

	//Functions used in the graph creation
	void SetMatriciesSizes(int height, int width);
	void CreateNodeMatrix(std::vector<std::vector<int>> matrix);
	void LinkNeighborsToList(std::vector<std::vector<int>> matrix);
	void SetNeighbors(int i, int j,std::vector<std::vector<int>> matrix, Node* node);
	Node* GetNode(int x, int y);

	Node* AboveNeighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	Node* BellowNeighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	Node* LeftNeighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	Node* RightNeighbor(int i, int  j, std::vector<std::vector<int>> matrix);
	
	void AddRow(std::vector<std::vector<int>> & m_nodes, std::vector<std::string> m_map, int row, int width);
	void Clenup(std::vector<std::vector<int>>& matrix);
	
	bool WeFoundGround(std::vector<std::string>  m_map, int i, int row);
	bool WeFoundLadder(std::vector<std::string> m_map, int i, int row);
	bool WeFoundPlayer(std::vector<std::string> m_map, int i, int row);
	bool WeFoundRope(std::vector<std::string> m_map, int i, int row);
	bool WeFoundEnemy(std::vector<std::string> m_map, int i, int row);
	bool WeFoundAir(std::vector<std::string> m_map, int i, int row);
	
	//Members
	std::vector<Node*> neighbor_list;
	std::vector<std::vector<Node*>> node_matrix;
};