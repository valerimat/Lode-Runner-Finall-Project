#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include "Graph.h"
#include <memory>
#include "StaticObject.h"	
#include "Enemy.h"
#include "Player.h"
class Coin;
class Present;
class Object;

class Map
{
public:
	//c-tors
	Map() = default;
	Map(std::vector<std::string>* map, int height,int width, int timer);
	~Map() = default;

	Map& operator=(Map& map)
	{
		return map;
	};
	
	// map functions
	void LoadTextures();
	void Draw(sf::RenderWindow& main_window);

	// getters
	Player* get_player();
	std::vector<Enemy*> GetEnemies();
	int GetHeight();
	int GetWidth();
	Graph & get_graph();

	int *GetTimer();

	void make_hole(sf::Vector2f location);
	void check_holes();
	void close_holes();

	// setters
	void SetObjects();

	// info
	void check_collision(Object& object);
	bool all_coins_collected();

	// action
	void DeleteCoin(Coin & coin);
	void DeletePresent(Present & present);
	void reset_positions();
private:
	int m_width;
	int m_height;
	int m_timer;

	char GetChar(int i, int j);

	Graph * m_graph;

	std::vector<std::string> m_map;

	std::vector<StaticObject*> m_holes;
	std::vector<StaticObject*> m_holes_to_close;
	std::vector<float> holes_time;

	std::vector<std::shared_ptr <sf::Texture>>  m_textures;

	std::vector<std::unique_ptr<StaticObject>>  m_static;
	std::vector<std::unique_ptr<DynamicObject>> m_dynamic;
};