#pragma once

//======include section======
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Macros.h"
#include "Map.h"
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

// send locations and your board
std::vector<int> CalculatePath(sf::Vector2f& from, sf::Vector2f & to, Map & board);



//helper functions - for full documentation visit cpp
void get_around(const Tile&, std::vector<Tile>&, const std::vector<Tile>, Map&, int);

bool check_validity(Tile, std::vector<Tile>, const Map&, enum Moves);

void calculate_score(std::vector<Tile>&, sf::Vector2f&, int);

int calculate_g_value(sf::Vector2f&,sf::Vector2f&);

int check_if_tile_in_vector(Tile, const std::vector<Tile>);

int find_the_best_score(std::vector<Tile>);

void init_arround(std::vector<Tile>&, sf::Vector2f&, const Map& board, const std::vector<Tile>&, int);

std::vector <int> make_path(std::vector<Tile>, Tile);





