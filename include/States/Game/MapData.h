#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//will hold core map data
class MapData
{
public:
	// c-tor
	MapData();

	// getters
	std::vector<std::string> * get_map(int number_of_level);
	int get_curr_height(int lvl);
	int get_curr_width(int lvl);
	int get_curr_time(int lvl);
	int get_num_of_levels();

private:
	// private function
	void load_maps();

	// members
	std::vector<std::vector<std::string>> m_maps;
	std::vector<int> m_timer;
	int m_number_of_levels;
};