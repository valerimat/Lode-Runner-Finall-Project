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
	int	curr_level = 0;

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
	DynamicObject * d_obj; // later to be changed Player player for proper use
	StaticObject static_object;
	Player* player;
	Enemy * enemy;

	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			switch(get_char(i,j))
			{
			case PLAYER: 
				player = new Player;
				player->init_object(PLAYER, sf::Vector2f(i, j));
				player->set_texture(m_textures[PLAYER_TEXTURE]);
				d_obj = player;
				m_dynamic.push_back(d_obj);

				break;
	
			case ENEMY:
				enemy = new Enemy;
				enemy->init_object(ENEMY, sf::Vector2f(i, j));
				enemy->set_texture(m_textures[ENEMY_TEXTURE]);
				enemy->set_smartness();
				d_obj = enemy;
				m_dynamic.push_back(d_obj);
				break;
	
			//case NONE:
			//	static_object.init_object(NONE, sf::Vector2f(i, j));
			//	static_object.set_texture(m_textures[NONE_TEXTURE]);
			//	m_static.push_back(static_object);
			//	break;

			case GROUND:
				static_object.init_object(GROUND, sf::Vector2f(i, j));
				static_object.set_texture(m_textures[GROUND_TEXTURE]);
				m_static.push_back(static_object);
				break;

			case LADDER:
				static_object.init_object(LADDER, sf::Vector2f(i, j));
				static_object.set_texture(m_textures[LADDER_TEXTURE]);
				m_static.push_back(static_object);
				break;

			case COIN:
				static_object.init_object(COIN, sf::Vector2f(i, j));
				static_object.set_texture(m_textures[COIN_TEXTURE]);
				m_static.push_back(static_object);
				break;

			case POLE:
				static_object.init_object(POLE, sf::Vector2f(i, j));
				static_object.set_texture(m_textures[POLE_TEXTURE]);
				m_static.push_back(static_object);
				break;
			}
		}
	}
}

void Map::Draw(sf::RenderWindow &main_window)
{
	// Background
	StaticObject background;

	float scale_height = float(m_height) * float(50) / float(HEIGHT),
		  scale_width  = float(m_width)  * float(50) / float(WIDTH);

	background.init_object(NULL, sf::Vector2f(0, 0));
	background.set_texture(m_textures[BACKGROUND_TEXTURE]);
	background.get_sprite().scale(scale_width, scale_height);

	background.Draw(main_window);

	// All the other objects
	for (int i = 0; i < m_static.size(); ++i)
	{
		m_static[i].Draw(main_window);
		sf::Vector2f vec(400, 750);
		if (m_static[i].in_bounds(vec))
		{
			//std::cout << i << ' ' << m_static[i].get_name() << ' ' << std::endl;
		}
	}
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		m_dynamic[i]->Draw(main_window);
		//std::cout << "X - " << m_dynamic[i].get_location().x << 
			//" Y - " << m_dynamic[i].get_location().y << std::endl;
	}
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

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("background.png");
	m_textures.push_back(texture_ptr);
}


char Map::get_char(int i,int j)
{
	return m_maps[0][i][j];
}

Player* Map::get_player() // later change to Player as a return value
{
	for (int i = 0; i < m_dynamic.size(); i++)
	{
		if (m_dynamic[i]->get_name() == PLAYER)
			return dynamic_cast<Player*>(m_dynamic[i]);
	}
	return NULL;
}


std::vector<Enemy*> Map::get_enemies()
{
	int index = 0;
	std::vector<Enemy*> temp;
	DynamicObject* DinamicPtr;
	std::shared_ptr< DynamicObject> d_ptr;

	while (index < m_dynamic.size())
	{
		if (m_dynamic[index]->get_name() == ENEMY)
		{
			temp.push_back(dynamic_cast<Enemy*>(m_dynamic[index]));
		}

		++index;
	}
	return temp;

}


char Map::what_is_there_bellow(sf::Vector2f & location)
{
	sf::Vector2f loc = location;
	loc.y += 55;

	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i].in_bounds(loc))
			return m_static[i].get_name();
	}
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		if (m_dynamic[i]->in_bounds(loc))
			return m_dynamic[i]->get_name();
	}

	return NONE;
}


char Map::what_is_there_on_the_side(sf::Vector2f& location)
{

	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i].in_bounds(location))
			return m_static[i].get_name();
	}
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		if (m_dynamic[i]->in_bounds(location))
			return m_dynamic[i]->get_name();
	}

	return NONE;
}

//checks if there is a collision based on the top right corner
//used mostly for ladders
char Map::collision_top_right(sf::Vector2f& location)
{

	for (int i = 0; i < m_static.size(); ++i)
	{
		//if the x is the same x and its somewhere on the y
		if (m_static[i].get_location().x == location.x && m_static[i].in_bounds(location))
			return m_static[i].get_name();
	}

	return NONE;
}

std::vector<StaticObject> Map::get_static()
{
	return m_static;
}
