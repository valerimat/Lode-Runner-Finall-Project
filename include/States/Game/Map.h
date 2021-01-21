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
	void load_textures();
	void Draw(sf::RenderWindow& main_window);

	// getters
	Player* get_player();
	std::vector<Enemy*> get_enemies();
	int get_height();
	int get_width();
	Graph & get_graph();

	int *get_timer();

	void make_hole(sf::Vector2f location);
	void check_holes();
	void close_holes();

	// setters
	void set_objects();

	// info
	void check_collision(Object& object);
	bool all_coins_collected();

	// action
	void delete_coin(Coin & coin);
	void delete_present(Present & present);
	void reset_positions();
private:

	void load_background();
	void check_dynamic_inside(RigidBodyObject& rigidBodyObject);


	int m_width;
	int m_height;
	int m_timer;

	char get_char(int i, int j);

	Graph * m_graph;

	std::vector<std::string> m_map;

	std::vector<RigidBodyObject*> m_holes;
	std::vector<RigidBodyObject*> m_holes_to_close;
	std::vector<float> holes_time;

	std::vector<std::unique_ptr<sf::Texture>>  m_textures;
	sf::Sprite  m_background;
	std::vector<std::unique_ptr<StaticObject>>  m_static;
	std::vector<std::unique_ptr<DynamicObject>> m_dynamic;
};