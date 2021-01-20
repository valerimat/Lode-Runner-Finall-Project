#include "Map.h"
#include "RigidBodyObject.h"
#include "Ladder.h"
#include "Pole.h"
#include "Present.h"
#include "Coin.h"
#include "Clock.h"
#include "Score.h"
#include "Music.h"
#include "Music.h"



// c-tor of map
//=============================================================================
Map::Map(std::vector<std::string>* map,int height, int width, int timer):
	m_map(*map),
	m_height(height),
	m_width(width),
	m_timer(timer)
{
	m_graph = new Graph(m_map, m_width, m_height);
	LoadTextures();
	LoadBackground();
	SetObjects();
}
//=============================================================================

//=============================================================================
Graph & Map::get_graph()
{
	return *m_graph;
}
//=============================================================================

// sets all the objects
//=============================================================================
void Map::SetObjects()
{

	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			sf::Vector2f location(i, j);

			switch(GetChar(i,j))
			{
			case PLAYER: 
				m_dynamic.push_back(
					std::make_unique<Player>(PLAYER, location, m_textures[PLAYER_TEXTURE].get()));
				break;

			case ENEMY:
				m_dynamic.push_back(
					std::make_unique<Enemy>(ENEMY, location, m_textures[ENEMY_TEXTURE].get()));
				break;

			case GROUND:
				m_static.push_back(
					std::make_unique<RigidBodyObject>(GROUND, location, m_textures[GROUND_TEXTURE].get()));
				break;

			case LADDER:
				m_static.push_back(
					std::make_unique<Ladder>(LADDER, location, m_textures[LADDER_TEXTURE].get()));
				break;

			case COIN:
				m_static.push_back(
					std::make_unique<Coin>(COIN, location, m_textures[COIN_TEXTURE].get()));
				break;

			case POLE:
				m_static.push_back(
					std::make_unique<Pole>(POLE, location, m_textures[POLE_TEXTURE].get()));
				break;

			case PRESENT:
				m_static.push_back(
					std::make_unique<Present>(PRESENT, location, m_textures[PRESENT_TEXTURE].get()));
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
//=============================================================================

// draws on window all the sprites
//=============================================================================
void Map::Draw(sf::RenderWindow &main_window)
{
	main_window.draw(m_background);


	// All the other objects
	for (int i = 0; i < m_static.size(); ++i)
	{	
		m_static[i]->Draw(main_window);
	}
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		m_dynamic[i]->Draw(main_window);
	}

}
//=============================================================================

// loads all the textures on shared ptr
//=============================================================================
void Map::LoadTextures()
{
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[0]->loadFromFile("ladder.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[1]->loadFromFile("ground.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[2]->loadFromFile("player.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[3]->loadFromFile("rope.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[4]->loadFromFile("enemy.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[5]->loadFromFile("coin.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[6]->loadFromFile("wall.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[7]->loadFromFile("background.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[8]->loadFromFile("ground with signs.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[9]->loadFromFile("present.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[10]->loadFromFile("maake.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[11]->loadFromFile("zevel.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[12]->loadFromFile("shop.png");
}
//=============================================================================

// gets char from the board
//=============================================================================
char Map::GetChar(int i,int j)
{
	return m_map[i][j];
}
//=============================================================================

// gets us the player ptr
//=============================================================================
Player* Map::get_player() // later change to Player as a return value
{
	for (int i = 0; i < m_dynamic.size(); i++)
	{
		if (m_dynamic[i]->get_name() == PLAYER)
			return (dynamic_cast<Player*>(m_dynamic[i].get()));
	}
}
//=============================================================================


// gets us vector of enemies ptr
//=============================================================================
std::vector<Enemy*> Map::GetEnemies()
{
	int index = 0;
	std::vector<Enemy*> temp;
	DynamicObject* DinamicPtr;


	while (index < m_dynamic.size())
	{
		if (m_dynamic[index]->get_name() == ENEMY)
		{
			temp.push_back(dynamic_cast<Enemy*>(m_dynamic[index].get()));
		}
		++index;
	}
	return temp;
}
//=============================================================================


//=============================================================================
int Map::GetWidth()
{
	return m_width;
}
//=============================================================================

//=============================================================================
int Map::GetHeight()
{
	return m_height;
}
//=============================================================================

//=============================================================================
int *Map::GetTimer()
{
	return &m_timer;
}
//=============================================================================


// deletes the coin
//=============================================================================
void Map::DeleteCoin(Coin & coin)
{
	
	auto i = 0;
	while (coin.get_location() != m_static[i]->get_location())
	{
		i++;
	}
	m_static.erase(m_static.begin() + i);
}
//=============================================================================

// deletes the present
//=============================================================================
void Map::DeletePresent(Present& present)
{
	auto i = 0;

	while (present.get_location() != m_static[i]->get_location())
	{
		i++;
	}
	switch (present.get_type())
	{
	case 0:
		std::cout << "time added\n";
		m_timer += 5;
		Music::GetMusic().DrinkingSound();
		break;
	case 1:
		std::cout << "lives added\n";
		get_player()->AddLives();
		Music::GetMusic().DrinkingSound();
		break;
	case 2:
		Score::GetScore().IncreasePoints();
		Music::GetMusic().DrinkingSound();
		break;
	case 3:
		std::shared_ptr<DynamicObject> dn_ptr;
		sf::Vector2f location = { 5,5 }; // needs to be a random location
		m_dynamic.push_back(std::make_unique<Enemy>(ENEMY, location, m_textures[ENEMY_TEXTURE].get()));
		//m_music->BadPresentSound();
		break;
	}
	m_static.erase(m_static.begin() + i);
}
//=============================================================================

//=============================================================================
void Map::check_collision(Object & object)
{
	
	//in for loop to not do read access violoation
	for(int i=0; i <m_static.size(); ++i)
	{
		if(m_static[i]->
			get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds()))

			m_static[i]->handle_collision(object);
	}

	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		if (m_dynamic[i]->
			get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds()))

			m_dynamic[i]->handle_collision(object);
	}
}
//=============================================================================

//=============================================================================
void Map::make_hole(sf::Vector2f location)
{
	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i]->get_sprite().getGlobalBounds().contains(location))
		{
			if (m_static[i]->make_hole())
			{
				m_holes.push_back(dynamic_cast<RigidBodyObject*>(m_static[i].get()));
				holes_time.push_back(Clock::GetClock().GetPassedSecondsFloat());
			}
		}
	}
}
//=============================================================================

//=============================================================================
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
//=============================================================================

//=============================================================================
void Map::close_holes()
{
	for (int i = 0; i < m_holes_to_close.size(); i++)
	{
		sf::Vector2f curr_scale = m_holes_to_close[i]->get_sprite().getScale();
		if (abs(curr_scale.y - (MacroSettings::GetSettings().GetScaleHeight())) < 0.01)
		{
			m_holes_to_close[i]->SetHole(false);
			m_holes_to_close.erase(m_holes_to_close.begin() + i);
			holes_time.erase(holes_time.begin() + i);
			continue;
		}

		m_holes_to_close[i]->RestOriginal();
		check_dynamic_inside(*m_holes_to_close[i]);
	}
}
//=============================================================================

//=============================================================================
bool Map::all_coins_collected()
{
	for (int i = 0; i < m_static.size(); ++i)
	{
		if (m_static[i]->get_name() == COIN)
			return false;
	}
	return true;
}
//=============================================================================

//=============================================================================
void Map::reset_positions()
{
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		m_dynamic[i]->reset_position();
	}
}
//=============================================================================


void Map::LoadBackground()
{
	float scale_height = float(HEIGHT) / 900.f,
		scale_width = float(WIDTH) / 1200.f;

	m_background.setTexture(*(m_textures[BACKGROUND_TEXTURE].get()));
	m_background.setPosition(sf::Vector2f(0, 50));
	m_background.scale(scale_width, scale_height);
}


void Map::check_dynamic_inside(RigidBodyObject& rigidBodyObject)
{
	for (int i = 0; i < m_dynamic.size(); ++i)
	{
		if (m_dynamic[i]->
			get_sprite().getGlobalBounds().intersects(rigidBodyObject.get_sprite().getGlobalBounds()))
		{
			if (m_dynamic[i]->IsInHole())
			{
				m_dynamic[i]->SetLocation(
					rigidBodyObject.get_location()
					+ 
					sf::Vector2f(0,- MacroSettings::GetSettings().GetSizeOfTile())
					);

				m_dynamic[i]->SetInHole(false);
			}
		}
	}
	
}