#include "Map.h"

Map::Map(std::vector<std::string>* map,int height, int width):
	m_map(*map),
	m_height(height),
	m_width(width)
{
	load_textures();
	set_objects();
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
	return m_map[i][j];
}

char Map::get_char(sf::Vector2f & location)
{
	return m_map[location.y][location.x];
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


bool Map::in_player(sf::Vector2f & location)
{
	if (get_player()->get_sprite().getGlobalBounds().contains(location))
		return true;
	else
		return false;
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


char Map::what_is_there_bellow(sf::Vector2f& location)
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


char Map::what_is_there(sf::Vector2f location)
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

bool Map::we_are_hanging_on_rope(sf::Vector2f& location_l, sf::Vector2f& location_r)
{

	for (int i = 0; i < m_static.size(); ++i)
	{
		//if the x is the same x and its somewhere on the y
		if ((m_static[i].get_location().y == location_l.y && m_static[i].in_bounds(location_l))
			|| (m_static[i].get_location().y == location_r.y && m_static[i].in_bounds(location_r)))
			return true;
	}
	return false;
}

std::vector<StaticObject> * Map::get_static()
{
	return  &m_static;
}

int Map::get_width()
{
	return m_width;
}

int Map::get_height()
{
	return m_height;
}


bool Map::out_of_boundrie(sf::Vector2f& location) {
	if (location.x <= 0)
		return true;
	else if (location.y > get_width())
		return true;
	else if (location.y < 0)
		return true;
	else if (location.x >= get_width())
		return true;

	return false;
}

sf::Vector2f Map::get_bounding_sprt_loc(sf::Vector2f location)
{
	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i].in_bounds(location))
			return m_static[i].get_location_x_y();
	}
}

bool Map::we_are_centerd(sf::Vector2f& location)
{
	//need to change to number based on tile size
	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i].get_location() == location)
			return true;
	}
	return false;
}




//location checks:
bool Map::is_ground(sf::Vector2f& location)
{
	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i].in_bounds(location))
			if (m_static[i].get_name() == GROUND)
				return true;
			else
				return false;
	}
	return false;
}
bool Map::is_ladder(sf::Vector2f& location)
{
	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i].in_bounds(location))
			if (m_static[i].get_name() == LADDER && m_static[i].get_location().x == location.x)
				return true;
			else
				return false;
	}
	return false;

}
