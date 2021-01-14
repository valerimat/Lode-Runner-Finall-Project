#include "Map.h"
#include "RigidBodyObject.h"
#include "Ladder.h"
#include "Pole.h"
#include "Present.h"
#include "Coin.h"


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
Graph Map::get_graph()
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
				dn_ptr = std::make_shared<Enemy>(ENEMY, location, m_textures[ENEMY_TEXTURE],smrt);
				m_dynamic.push_back(dn_ptr);
				smrt++;
				break;

			case GROUND:
				st_ptr = std::make_shared<RigidBodyObject>(GROUND, location, m_textures[GROUND_TEXTURE]);
				m_static.push_back(st_ptr);
				m_ground.push_back(st_ptr);
				break;

			case LADDER:
				st_ptr = std::make_shared<Ladder>(LADDER, location, m_textures[LADDER_TEXTURE]);
				m_static.push_back(st_ptr);
				m_ladders.push_back(st_ptr);
					
				break;

			case COIN:
				st_ptr = std::make_shared<Coin>(LADDER, location, m_textures[COIN_TEXTURE]);
				m_static.push_back(st_ptr);
				m_coins.push_back(st_ptr);
				break;

			case POLE:
				st_ptr = std::make_shared<Pole>(POLE, location, m_textures[POLE_TEXTURE]);
				m_static.push_back(st_ptr);
				m_poles.push_back(st_ptr);
				break;

			case PRESENT:
				st_ptr = std::make_shared<Present>(PRESENT, location, m_textures[PRESENT_TEXTURE]);
				m_static.push_back(st_ptr);
				m_presents.push_back(st_ptr);
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

	for (int i = 0; i < m_presents.size(); ++i)
	{
		m_presents[i]->Draw(main_window);
	}

	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		m_dynamic[i]->Draw(main_window);
	}

	m_graph->Draw(main_window);
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
Player* Map::GetPlayer() // later change to Player as a return value
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

// asks if it touches the player
bool Map::IsOnPlayer(sf::Vector2f & location)
{
	if (GetPlayer()->get_sprite().getGlobalBounds().contains(location))
		return true;
	else
		return false;
}
//-----------------------------------------------------------------------------

// whats next basiclly 
char Map::WhatIsThere(sf::Vector2f location)
{

	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i]->in_bounds(location))
			return m_static[i]->get_name();
	}
	return NONE;
}
//-----------------------------------------------------------------------------

// asks if it touches the ground
bool Map::IsOnGround(sf::Vector2f location)
{
	sf::Vector2f player_location = GetPlayer()->get_location();

	std::cout << player_location.x << " " << player_location.y << std::endl;

	for (int i = 0; i < m_ground.size(); ++i)
	{
		if (m_ground[i]->in_bounds(player_location))
			//m_music->LadderSound();
			std::cout << "yes\n";
		if (m_ground[i]->in_bounds(location))
			return true;
	}
	return false;
}
//-----------------------------------------------------------------------------

// asks if it touches the coin
int Map::IsOnCoin(sf::Vector2f location)
{
	location.y += 1;

	for (int i = 0; i < m_coins.size(); ++i)
	{
		if (m_coins[i]->in_bounds(location))
			return i;
	}
	return -1;
}
//-----------------------------------------------------------------------------

// asks if it touches the coin
int Map::IsOnPresent(sf::Vector2f location)
{
	location.y -= 1;

	for (int i = 0; i < m_presents.size(); ++i)
	{
		if (m_presents[i]->in_bounds(location))
		{
			return i;
			std::cout << "yes\n";
		}
	}
	return -1;
}
//-----------------------------------------------------------------------------

// asks if it touches the rope
bool Map::IsOnRope(sf::Vector2f location_l, sf::Vector2f location_r)
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
//-----------------------------------------------------------------------------

// asks if it touches the ladder
bool Map::IsOnLadder(sf::Vector2f location)
{
	sf::RectangleShape rect;
	//sf::Vector2f play_location = GetPlayer()->get_location();
	rect.setPosition(location);
	rect.setSize({ 40,40 });

	for (int i = 0; i < m_ladders.size(); ++i)
	{
		//if (m_ladders[i]->in_bounds(play_location))
			//m_music->LadderSound();

		if (m_ladders[i]->in_bounds(rect))
			return true;
	}
	return false;
}
//-----------------------------------------------------------------------------

// deletes the coin
void Map::DeleteCoin(Coin & coin)
{
	int i = 0;
	while (coin.get_location() != m_coins[i]->get_location())
	{
		i++;
	}

	m_coins.erase(m_coins.begin() + i);
	i = 0;
	while (coin.get_location() != m_static[i]->get_location() && m_static[i]->get_name() != COIN)
	{
		i++;
	}
	m_static.erase(m_static.begin() + i);
	m_music->EaitngSound();
}
//-----------------------------------------------------------------------------

// deletes the present
void Map::DeletePresent(Present & prenset)
{
	int i = 0;
	while (prenset.get_location() != m_presents[i]->get_location())
	{
		i++;
	}
	m_presents.erase(m_presents.begin() + i);
	i = 0;
	while (prenset.get_location() != m_static[i]->get_location() && m_static[i]->get_name() != PRESENT)
	{
		i++;
	}
	m_timer += 5;
	m_static.erase(m_static.begin() + i);
	m_music->DrinkingSound();
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
