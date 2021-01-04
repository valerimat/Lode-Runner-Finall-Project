#pragma once

//======include section======
#include <vector>
#include <SFML/Graphics.hpp>
#include "Macros.h"
class Tile;
class Map;
class Enemy;
#include <math.h>

//==============================================================================
//   ______            ______   ________  ______   _______  
//  /      \          /      \ /        |/      \ /       \ 
// /$$$$$$  |        /$$$$$$  |$$$$$$$$//$$$$$$  |$$$$$$$  |
// $$ |__$$ | ______ $$ \__$$/    $$ |  $$ |__$$ |$$ |__$$ |
// $$    $$ |/      |$$      \    $$ |  $$    $$ |$$    $$< 
// $$$$$$$$ |$$$$$$/  $$$$$$  |   $$ |  $$$$$$$$ |$$$$$$$  |
// $$ |  $$ |        /  \__$$ |   $$ |  $$ |  $$ |$$ |  $$ |
// $$ |  $$ |        $$    $$/    $$ |  $$ |  $$ |$$ |  $$ |
// $$/   $$/          $$$$$$/     $$/   $$/   $$/ $$/   $$/
//==============================================================================

/*
Algorithm for calcluating shortest path for monsters
*/
namespace Astar
{
	// send locations and your board
	std::vector<NextStep> calc_path(Map* map, Enemy* enemy);

	//helper functions - for full documentation visit cpp
	void get_around(Tile& curr_tile,
		std::vector<Tile>& arround,
		const std::vector<Tile> closed_list,
		Map* map,
		int index_of_father,
		Enemy* enemy);

	int found_player(std::vector<Tile>& tiles, sf::Vector2f location);

	void calculate_score(std::vector<Tile>&, sf::Vector2f&, int);

	int calculate_g_value(sf::Vector2f&, sf::Vector2f&);

	int check_if_tile_in_vector(Tile, const std::vector<Tile>);

	int find_the_best_score(std::vector<Tile>);

	std::vector <NextStep> make_path(std::vector<Tile>, Tile);



}

