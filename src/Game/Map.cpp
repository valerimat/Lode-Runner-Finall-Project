#include "Map.h"
#include "RigidBodyObject.h"
#include "Ladder.h"
#include "Pole.h"
#include "Present.h"
#include "Coin.h"
#include "Clock.h"


// c-tor of map
Map::Map(std::vector<std::string>* map,int height, int width, int timer):
	m_map(*map),
	m_height(height),
	m_width(width),
	m_timer(timer)
{
	m_graph = new Graph(m_map, m_width, m_height);
	LoadTextures();
	SetObjects();
}
//-----------------------------------------------------------------------------
Graph & Map::get_graph()
{
	return *m_graph;
}
// sets all the objects
void Map::SetObjects()
{

	std::shared_ptr<StaticObject> st_ptr;
	std::shared_ptr<DynamicObject> dn_ptr;
	std::shared_ptr<Consumables> coin_ptr;
	
	int smrt = 0;

	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			sf::Vector2f location(i, j);

			switch(GetChar(i,j))
			{
			case PLAYER: 
				dn_ptr = std::make_shared<Player>(PLAYER, location, m_textures[PLAYER_TEXTURE]);
				m_dynamic.push_back(dn_ptr);
				break;

			case ENEMY:
				dn_ptr = std::make_shared<Enemy>(ENEMY, location, m_textures[ENEMY_TEXTURE]);
				m_dynamic.push_back(dn_ptr);
				break;

			case GROUND:
				st_ptr = std::make_shared<RigidBodyObject>(GROUND, location, m_textures[GROUND_TEXTURE]);
				m_static.push_back(st_ptr);
				break;

			case LADDER:
				st_ptr = std::make_shared<Ladder>(LADDER, location, m_textures[LADDER_TEXTURE]);
				m_static.push_back(st_ptr);
				break;

			case COIN:
				st_ptr = std::make_shared<Coin>(COIN, location, m_textures[COIN_TEXTURE]);
				m_static.push_back(st_ptr);
				break;

			case POLE:
				st_ptr = std::make_shared<Pole>(POLE, location, m_textures[POLE_TEXTURE]);
				m_static.push_back(st_ptr);
				break;

			case PRESENT:
				st_ptr = std::make_shared<Present>(PRESENT, location, m_textures[PRESENT_TEXTURE]);
				m_static.push_back(st_ptr);
				break;

			/*
			// the cases below represent decorations
			case 'G':
				st_ptr = std::make_shared<StaticObject>(GROUND, location, m_textures[GROUND_W_SIGNS_TEXTURE]);
				m_static.push_back(st_ptr);
				m_ground.push_back(st_ptr);
				break;
			
			case 'M':
				st_ptr = std::make_shared<StaticObject>(' ', location, m_textures[MAAKE_TEXTURE]);
				m_static.push_back(st_ptr);
				break;

			case 'Z':
				st_ptr = std::make_shared<StaticObject>(' ', location, m_textures[ZEVEL_TEXTURE]);
				m_static.push_back(st_ptr);
				break;
			case 'S':
				st_ptr = std::make_shared<StaticObject>(' ', location, m_textures[SHOP_TEXTURE]);
				m_static.push_back(st_ptr);
				break;
			*/
			}
		}
	}
}
//-----------------------------------------------------------------------------

// draws on window all the sprites
void Map::Draw(sf::RenderWindow &main_window)
{
	// Background
	float scale_height = float(m_height) * float(50) / float(HEIGHT),
		  scale_width  = float(m_width)  * float(50) / float(WIDTH);
	// scales the background so it will fit nicely in the game
	StaticObject background(NULL, sf::Vector2f(1, 0), m_textures[BACKGROUND_TEXTURE]);
	background.get_sprite().scale(scale_width, scale_height);
	background.Draw(main_window);


	// All the other objects
	for (int i = 0; i < m_static.size(); ++i)
	{	
		m_static[i]->Draw(main_window);
	}
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		std::cout << m_dynamic.size() << std::endl;
		m_dynamic[i]->Draw(main_window);
	}

	//m_graph->Draw(main_window);
}
//-----------------------------------------------------------------------------

// loads all the textures on shared ptr
void Map::LoadTextures()
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

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("present.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("maake.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("zevel.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("shop.png");
	m_textures.push_back(texture_ptr);
}
//-----------------------------------------------------------------------------

// gets char from the board
char Map::GetChar(int i,int j)
{
	return m_map[i][j];
}
//-----------------------------------------------------------------------------

// gets us the player ptr
Player* Map::get_player() // later change to Player as a return value
{
	for (int i = 0; i < m_dynamic.size(); i++)
	{
		if (m_dynamic[i]->get_name() == PLAYER)
			return dynamic_cast<Player*>(&(*m_dynamic[i]));
	}
	return NULL;
}
//-----------------------------------------------------------------------------

// gets us vector of enemies ptr
std::vector<Enemy*> Map::GetEnemies()
{
	int index = 0;
	std::vector<Enemy*> temp;
	DynamicObject* DinamicPtr;
	std::shared_ptr< DynamicObject> d_ptr;

	while (index < m_dynamic.size())
	{
		if (m_dynamic[index]->get_name() == ENEMY)
		{
			temp.push_back(dynamic_cast<Enemy*>(&(*m_dynamic[index])));
		}
		++index;
	}
	return temp;
}
//-----------------------------------------------------------------------------

std::vector<std::shared_ptr<StaticObject>>* Map::GetStatic()
{
	return  &m_static;
}
//-----------------------------------------------------------------------------

int Map::GetWidth()
{
	return m_width;
}
//-----------------------------------------------------------------------------

int Map::GetHeight()
{
	return m_height;
}
//-----------------------------------------------------------------------------

int *Map::GetTimer()
{
	return &m_timer;
}
//-----------------------------------------------------------------------------


// deletes the coin
void Map::DeleteCoin(Coin & coin)
{
	
	auto i = 0;
	while (coin.get_location() != m_static[i]->get_location())
	{
		i++;
	}
	m_static.erase(m_static.begin() + i);
}
//-----------------------------------------------------------------------------

// deletes the present
void Map::DeletePresent(Present &present)
{
	auto i = 0;

	while (present.get_location() != m_static[i]->get_location())
	{
		i++;
	}
	switch(present.get_type())
	{
	case 0:
		m_timer += 5;
		break;
	case 1:
		// add life
		break;
	case 2:
		// add points
		break;
	case 3:
		std::cout << "enemy has spawned\n";
		std::shared_ptr<DynamicObject> dn_ptr;
		sf::Vector2f location = { 5,5 };
		dn_ptr = std::make_shared<Enemy>(ENEMY, location, m_textures[ENEMY_TEXTURE]);
		m_dynamic.push_back(dn_ptr);
		break;
	}
	m_static.erase(m_static.begin() + i);
}
//-----------------------------------------------------------------------------

void Map::check_collision(Object & object)
{
	
	//in for loop to not do read access violoation
	for(int i=0; i <m_static.size(); ++i)
	{
		if(m_static[i]->get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds()))
			m_static[i]->handle_collision(object);
	}

	for (auto d_object : m_dynamic)
	{
		if (d_object->get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds()))
			d_object->handle_collision(object);
	}
}
//-----------------------------------------------------------------------------


void Map::make_hole(sf::Vector2f location)
{
	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i]->get_sprite().getGlobalBounds().contains(location))
		{
			if (m_static[i]->make_hole())
			{
				m_holes.push_back(m_static[i]);
				holes_time.push_back(Clock::GetClock().GetPassedSecondsFloat());
			}
		}
	}
}
//-----------------------------------------------------------------------------

void Map::check_holes()
{
	for (int i = 0; i < m_holes.size(); i++)
	{
		if (Clock::GetClock().GetPassedSecondsFloat()  - holes_time[i]  > 4)
		{
			m_holes_to_close.push_back(m_holes[i]);
			m_holes.erase(m_holes.begin()  +i);
		}
	}
}
//-----------------------------------------------------------------------------

void Map::close_holes()
{
	for (int i = 0; i < m_holes_to_close.size(); i++)
	{
		sf::Vector2f curr_scale = m_holes_to_close[i]->get_sprite().getScale();
		if (abs(curr_scale.y - (0.8)) < 0.00001)
		{
			m_holes_to_close[i]->m_hole = false;
			m_holes_to_close.erase(m_holes_to_close.begin() + i);
			holes_time.erase(holes_time.begin() + i);
			continue;
		}
		m_holes_to_close[i]->get_sprite().move(sf::Vector2f(0, -5));
		m_holes_to_close[i]->get_sprite().setScale(curr_scale + sf::Vector2f(0, 0.1));
		m_holes_to_close[i]->get_sprite().setColor(sf::Color(255, 255, 255, 255));
	}
}
//-----------------------------------------------------------------------------

bool Map::all_coins_collected()
{
	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i]->get_name() == COIN)
			return false;
	}
	return true;
}

//-----------------------------------------------------------------------------


void Map::reset_positions()
{
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		m_dynamic[i]->reset_position();
	}
}

