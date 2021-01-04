#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//will hold core map data
class MapData
{
public:
	MapData();
	std::vector<std::string> * get_map(int number_of_level);
	std::vector<std::string> * get_map_clean(int number_of_levle);
	int get_curr_height(int lvl);
	int get_curr_width(int lvl);
private:
	void LoadMaps();
	std::vector <std::vector <std::string>> m_maps_clean;
	std::vector<std::vector<std::string>> m_maps;
	int m_number_of_levels;
};