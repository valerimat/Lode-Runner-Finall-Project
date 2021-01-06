#include "Astar.h"
#include "Map.h"
#include "Enemy.h"
#include "Tile.h"
#include "EnemyController.h"

std::vector<NextStep> Astar::calc_path(Map* map, EnemyController& controller, sf::Vector2f&& location)
{

	sf::Vector2f player_location = map->GetPlayer()->get_location();

	// will store open list of tiles
	std::vector<Tile> open_list;

	// will store closed list of tiles
	std::vector<Tile> closed_list;

	// will store the path
	std::vector<NextStep> path;

	//will store the tiles around our tile
	std::vector<Tile> arround;

	//starting tile
	Tile from_where(location, 0,NextStep::NONE, 0);


	//end tile
	Tile to_where(player_location, 0, NextStep::NONE, 0);

	//iterator
	std::vector<Tile>::iterator tile_to_add;

	//push the first tile to the open list
	open_list.push_back(from_where);

	//set the h_score -NEED TO SET h_score based on father
	int h_score = 1;

	int index_of_wanted_tile = 0;

	int index_of_father = 0;

	while (true) {
		//fail safe
		if (open_list.size() == 0) {
			std::vector<NextStep> path;
			int i = 0;
			while (i < 10)
			{
				path.push_back(NextStep::NONE);
				++i;
			}
			return path;
		}

		//reset arround list
		arround.clear();

		//get the index of the tile if the loweest score from the open list
		index_of_wanted_tile = find_the_best_score(open_list);

		// add it to the closed list
		closed_list.push_back(open_list[index_of_wanted_tile]);

		//set the iterator to the node we jsut pushed
		tile_to_add = open_list.begin() + index_of_wanted_tile;

		//erase the node from open list
		open_list.erase(tile_to_add);

		//gets all posible tiles around
		get_around(*(closed_list.end() - 1), arround, closed_list,closed_list.size() - 1, controller);

		//calculates theyr score
		calculate_score(arround, to_where.m_location, h_score);


		int index = 0;
		int tile_in_open = 0;

		//run on all tiles around
		while (index < arround.size()) {

			//check if they are in open
			tile_in_open = check_if_tile_in_vector(arround[index], open_list);

			//if there is no such tile
			if (tile_in_open == -1)
				open_list.push_back(arround[index]);

			//if its in the open list
			else
				//if the f value is better now
				if (arround[index].f_value < open_list[tile_in_open].f_value)
					//update this tile to be in open and remove the prev
					open_list[tile_in_open] = arround[index];
			index++;
		}

		int index_of_player_tile = found_player(open_list, player_location);
		if (index_of_player_tile != -1)
		{
			closed_list.push_back(open_list[index_of_player_tile]);
			break;
		}
		index_of_father++;

		if (closed_list.size() > 1500)
		{
			std::vector<NextStep> path;
			int i = 0;
			while (i < 20)
			{
				path.push_back(NextStep::NONE);
				++i;
			}
			return path;
		}
			
	}

	

	path = make_path(closed_list, from_where);

	return path;
}

//====================================================================================
//getting the tiles arround our tile based on the alogrithm
void Astar::get_around(Tile& curr_tile,
	std::vector<Tile>& arround,
	const std::vector<Tile> closed_list,
	int index_of_father,
	EnemyController & controller)
{
	sf::Vector2f curr_location = curr_tile.m_location;

	sf::Vector2f above(curr_location.x, curr_location.y - 10),
		below(curr_location.x, curr_location.y + 10),
		right_l(curr_location.x + 10, curr_location.y),
		left_l(curr_location.x - 10, curr_location.y);

	std::vector<NextStep> avaliavle_steps = controller.get_avaliable_steps(curr_location);
	

	for (int i = 0; i < avaliavle_steps.size(); ++i)
	{
		Tile new_tile;
		switch (avaliavle_steps[i])
		{
		case NextStep::UP:
			new_tile= Tile(above, index_of_father, NextStep::UP, curr_tile.h_value + 1);
			arround.push_back(new_tile);
			break;
		case NextStep::DOWN:
			new_tile = Tile(below, index_of_father, NextStep::DOWN, curr_tile.h_value + 1);
			arround.push_back(new_tile);
			break;
		case NextStep::LEFT:
			new_tile = Tile(left_l, index_of_father, NextStep::LEFT, curr_tile.h_value + 1);
			arround.push_back(new_tile);
			break;
		case NextStep::RIGHT:
			new_tile = Tile(right_l, index_of_father, NextStep::RIGHT, curr_tile.h_value + 1);
			arround.push_back(new_tile);
			break;
		case NextStep::NONE:
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < arround.size(); i++)
	{
		int index = check_if_tile_in_vector(arround[i], closed_list);

		if (index >= 0)
			arround.erase(arround.begin() + i);
	}

}
//====================================================================================


//calculates the f score based on g and h
void Astar::calculate_score(std::vector<Tile>& arround,
	sf::Vector2f & to,
	int h_score)
{
	int size = arround.size();
	int index = 0;

	//runing on around tiles
	while (index < size) {
		arround[index].h_value = h_score;
		arround[index].g_value = calculate_g_value(arround[index].m_location, to);
		arround[index].f_value = arround[index].h_value + arround[index].g_value;
		index++;
	}
}
//====================================================================================

//calculating g value based on manhattan algorithm
int Astar::calculate_g_value(sf::Vector2f& from, sf::Vector2f& to)
{
	return abs((from.y - to.y)) + abs(from.x - to.x);
}
//====================================================================================

//cehck if a specific tile in a vector BASED ON LOCATION
int Astar::check_if_tile_in_vector(Tile tile, std::vector<Tile> open_list) {
	int size = open_list.size();

	int index = 0;

	while (index < size) {

		if (tile.m_location == open_list[index].m_location) {
			return index;
		}

		++index;
	}

	return -1;
}
//====================================================================================
//find the tile with the best score
int Astar::find_the_best_score(std::vector<Tile> open_list) {
	Tile new_tile;
	size_t end_of_open = open_list.size();
	new_tile = open_list[end_of_open - 1];

	int index = 0;
	int tile_index = end_of_open - 1;
	int size = open_list.size();

	while (index < size)
	{
		if (new_tile.f_value > open_list[index].f_value) {
			new_tile = open_list[index];
			tile_index = index;
		}
		index++;
	}

	index--;

	return tile_index;

}

int Astar::found_player(std::vector<Tile> & tiles, sf::Vector2f location)
{
	sf::Vector2f offset_r(SIZE_OF_TILE -1, -1);
	sf::Vector2f offset_d(0, SIZE_OF_TILE -1);
	sf::Vector2f offset_d_r(SIZE_OF_TILE +1, SIZE_OF_TILE-1);
	for (int i = 0; i < tiles.size(); ++i)
	{
		sf::RectangleShape rect;
		rect.setPosition(tiles[i].m_location);
		rect.setSize(sf::Vector2f(tiles[i].m_size, tiles[i].m_size));

		if (rect.getGlobalBounds().contains(location))
			return i;
		else if (rect.getGlobalBounds().contains(location + offset_r))
			return i;
		else if (rect.getGlobalBounds().contains(location + offset_d_r))
			return i;
		else if (rect.getGlobalBounds().contains(location + offset_d))
			return i;
	}	
	return -1;
}



//====================================================================================
//makes path out of a closed list
std::vector <NextStep> Astar::make_path(std::vector < Tile> closed, Tile to) {

	int index = 0;
	std::vector <NextStep> path;
	std::vector <NextStep> path_finall;
	Tile curr_tile = *(closed.end() - 1);
	int index_of_father = curr_tile.m_father;

	while (closed[index_of_father].m_location != (*(closed.begin())).m_location ||
		 path.size() > 999) {

		path.insert(path.begin(), closed[index_of_father].m_move);

		index_of_father = closed[index_of_father].m_father;

	}
	if (closed.size() == 2)
		path.insert(path.begin(), closed[1].m_move);

	//path.insert(path.begin(), closed[index_of_father].m_move);
	for (int i = 0; i < path.size(); ++i)
	{
		for (int j = 0; j < 10; ++j)
			path_finall.push_back(path[i]);
	}
	return path_finall;
}


