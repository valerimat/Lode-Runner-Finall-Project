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
	std::vector<std::string> * GetMap(int number_of_level);
	std::vector<std::string> * GetCleanMap(int number_of_levle);
	int GetCurrHeight(int lvl);
	int GetCurrWidth(int lvl);

private:
	// private function
	void LoadMaps();

	// members
	std::vector <std::vector <std::string>> m_maps_clean;
	std::vector<std::vector<std::string>> m_maps;
	int m_number_of_levels;
};