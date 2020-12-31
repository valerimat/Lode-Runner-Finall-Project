#include "Map.h"


Map::Map()
{
	load_maps();
	load_textures();
	set_objects();
}

//Will hold all maps in a vector of vector of strings for level update
void Map::load_maps()
{
	curr_level = 0;

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
}


void Map::set_objects()
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			switch(get_char(i,j))
			{
			case PLAYER:
				m_dinamic.push_back(DinamicObject(PLAYER,sf::Vector2f( i, j)));
				m_dinamic(m_dinamic.back() - 1).set_texture(*m_textures[PLAYER_TEXTURE]);
				break;

			case ENEMY:
				m_dinamic.push_back(DinamicObject(ENEMY, sf::Vector2f(i, j)));
				m_dinamic(m_dinamic.back() - 1).set_texture(*m_textures[ENEMY_TEXTURE]);
				break;
		
			case NONE:
				m_static.push_back(StaticObject(NONE,sf::Vector2f(i, j)));
				m_static(m_static.back() - 1).set_texture(*m_textures[NONE_TEXTURE]);
				break;

			case GROUND:
				m_static.push_back(StaticObject(GROUND, sf::Vector2f(i, j)));
				m_static(m_static.back() - 1).set_texture(*m_textures[GROUND_TEXTURE]);
				break;

			case LADDER:
				m_static.push_back(StaticObject(LADDER, sf::Vector2f(i, j)));
				m_static(m_static.back() - 1).set_texture(*m_textures[LADDER_TEXTURE]);
				break;

			case COIN:
				m_static.push_back(StaticObject(COIN,sf::Vector2f(i, j)));
				m_static(m_static.back() - 1).set_texture(*m_textures[COIN_TEXTURE]);
				break;

			case POLE:
				m_static.push_back(StaticObject(POLE, sf::Vector2f(i, j)));
				m_static(m_static.back() - 1).set_texture(*m_textures[POLE_TEXTURE]);
				break;
			}
		}
	}
}

void Map::Draw(sf::RenderWindow &main_window)
{
	for (int i = 0; i < m_static.size(); ++i)
		m_static[i].Draw(main_window);

	for (int i = 0; i < m_dinamic.size(); ++i)
		m_dinamic[i].Draw(main_window);

}

void Map::load_textures()
{
	auto texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("ladder.png");
	m_textures.push_back(texture_ptr);


	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("ground.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("player.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("rope.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("enemy.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("coin.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("wall.png");
	m_textures.push_back(texture_ptr);

}
