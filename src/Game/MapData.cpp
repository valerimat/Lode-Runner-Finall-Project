#include "MapData.h"

// c-tor
MapData::MapData()
{
	LoadMaps();
}
//-----------------------------------------------------------------------------

// loads maps
void MapData::LoadMaps()
{
	int	curr_level = 0;
	int m_height;
	int m_width;
	int timer;

	std::string   str; // temporary string which we push into the vector;
	std::ifstream file;


	file.open("Board.txt"); // Board.txt has the all levels 

	if (!file)
	{
		std::cout << "File didn't open\n";
		exit(EXIT_FAILURE);
	}
	char N;

	int idex_of_levle = 0;

	while (file.peek() != EOF)
	{
		std::vector<std::string> m_vector_of_strings; // will hold 2D array of the map and its content
		std::vector<std::string> m_clean_vector_of_strings;

		file >> m_height;
		file >> m_width;
		file >> timer;

		m_timer.push_back(timer);

		int index = 0;

		do
		{
			//reads each line from the Board.txt
			getline(file, str);

			// Line contains string of length > 0 then save it in vector
			if (str.size() > 0)
			{
				m_vector_of_strings.push_back(str);
				m_clean_vector_of_strings.push_back(str);
			}
			index++;
		}
		// Read the next line from File untill it reaches empty row.
		while (index <= m_height);

		m_maps.push_back(m_vector_of_strings);

		for (int i = 0; i < m_vector_of_strings.size(); i++)
		{

			for (int j = 0; j < m_vector_of_strings[i].size(); j++)
			{
				if (m_vector_of_strings[i][j] == '@' ||
					m_vector_of_strings[i][j] == '%' ||
					m_vector_of_strings[i][j] == '*')

					m_clean_vector_of_strings[i][j] = ' ';
			}
		}
		m_maps_clean.push_back(m_clean_vector_of_strings);

		m_vector_of_strings.clear();
		m_clean_vector_of_strings.clear();
	}
	m_number_of_levels = m_maps.size();

}
//-----------------------------------------------------------------------------

// gets the map
std::vector<std::string> * MapData::GetMap(int number_of_level)
{
	if (number_of_level < m_number_of_levels)
		return  &m_maps[number_of_level];

	else
		return NULL;
}
//-----------------------------------------------------------------------------

// gets a clean map
std::vector<std::string> * MapData::GetCleanMap(int number_of_level)
{
	if (number_of_level < m_number_of_levels)
		return  &m_maps_clean[number_of_level];

	else
		return NULL;
}
//-----------------------------------------------------------------------------

// gets the current height
int MapData::GetCurrHeight(int lvl)
{
	return m_maps[lvl].size();
}
//-----------------------------------------------------------------------------

// gets the current width
int MapData::GetCurrWidth(int lvl)
{
	return m_maps[lvl][0].size();
}
//-----------------------------------------------------------------------------

// gets the current width
int MapData::GetCurrTimer(int lvl)
{
	return m_timer[lvl];
}