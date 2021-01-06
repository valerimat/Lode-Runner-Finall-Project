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
	DynamicObject * d_obj;
	StaticObject * static_object;
	Consumables * coins;
	std::shared_ptr<StaticObject> st_ptr;
	std::shared_ptr<Consumables> coin_ptr;
	Player* player;
	Enemy * enemy;
	int smrt = 0;

	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			sf::Vector2f location(i, j);

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
				enemy->set_smartness(smrt);
				enemy->set_texture(m_textures[ENEMY_TEXTURE]);
				d_obj = enemy;
				m_dynamic.push_back(d_obj);
				smrt++;
				break;

			case GROUND:
				st_ptr = std::make_shared<StaticObject>(GROUND, location, m_textures[GROUND_TEXTURE]);
				m_static.push_back(st_ptr);
				m_ground.push_back(st_ptr);
				break;

			case 'G':
				st_ptr = std::make_shared<StaticObject>(GROUND, location, m_textures[GROUND_W_SIGNS_TEXTURE]);
				m_static.push_back(st_ptr);
				m_ground.push_back(st_ptr);
				break;

			case LADDER:
				st_ptr = std::make_shared<StaticObject>(LADDER, location, m_textures[LADDER_TEXTURE]);
				m_static.push_back(st_ptr);
				m_ladders.push_back(st_ptr);
					
				break;

			case COIN:
				st_ptr = std::make_shared<StaticObject>(LADDER, location, m_textures[COIN_TEXTURE]);
				m_coins.push_back(st_ptr);
				break;

			case POLE:
				st_ptr = std::make_shared<StaticObject>(POLE, location, m_textures[POLE_TEXTURE]);
				m_static.push_back(st_ptr);
				m_poles.push_back(st_ptr);
				break;
			}
		}
	}
}


void Map::Draw(sf::RenderWindow &main_window)
{
	// Background
	

	float scale_height = float(m_height) * float(50) / float(HEIGHT),
		  scale_width  = float(m_width)  * float(50) / float(WIDTH);

	StaticObject background(NULL, sf::Vector2f(0, 0), m_textures[BACKGROUND_TEXTURE]);
	background.get_sprite().scale(scale_width, scale_height);

	background.Draw(main_window);

	// All the other objects
	for (int i = 0; i < m_static.size(); ++i)
	{	
		m_static[i]->Draw(main_window);
	}

	for (int i = 0; i < m_coins.size(); ++i)
	{
		m_coins[i]->Draw(main_window);
	}

	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		m_dynamic[i]->Draw(main_window);
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

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("ground with signs.png");
	m_textures.push_back(texture_ptr);
}


char Map::get_char(int i,int j)
{
	return m_map[i][j];
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


char Map::what_is_there(sf::Vector2f location)
{

	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i]->in_bounds(location))
			return m_static[i]->get_name();
	}
	return NONE;
}


bool Map::is_there_ground(sf::Vector2f location)
{
	for (int i = 0; i < m_ground.size(); ++i)
	{
		if (m_ground[i]->in_bounds(location))
			return true;
	}
	return false;
}

int Map::is_on_coin(sf::Vector2f location)
{
	location.y += 1;

	for (int i = 0; i < m_coins.size(); ++i)
	{
		if (m_coins[i]->in_bounds(location))
			return i;
	}
	return -1;
}

void Map::delete_coin(int i)
{
	m_coins.erase(m_coins.begin() + i);
}



bool Map::we_are_hanging_on_rope(sf::Vector2f location_l, sf::Vector2f location_r)
{
	for (int i = 0; i < m_poles.size(); ++i)
	{
		//if the x is the same x and its somewhere on the y
		if (m_poles[i]->in_bounds(location_l)) {
			if ((m_poles[i]->get_location().y == location_l.y))
				return true;

			return false;
		}
		else if (m_poles[i]->in_bounds(location_r)) {
			if ((m_poles[i]->get_location().y == location_r.y))
				return true;

			return false;
		}
	}
	return false;
}


bool Map::we_are_on_ladder(sf::Vector2f location)
{
	sf::RectangleShape rect;
	rect.setPosition(location);
	rect.setSize({ 40,40 });

	for (int i = 0; i < m_ladders.size(); ++i)
	{
		if (m_ladders[i]->in_bounds(rect))
				return true;
	}
	return false;
}
std::vector<std::shared_ptr<StaticObject>>* Map::get_static()
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


bool Map::out_of_boundrie(sf::Vector2f location) {
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

int Map::get_coin_size()
{
	return m_coins.size();
}



