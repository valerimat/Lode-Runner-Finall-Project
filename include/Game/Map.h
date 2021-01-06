#pragma once
#include <vector>
#include <string>
#include "StaticObject.h"
#include "Consumables.h"
//#include "DynamicObject.h"
#include "Macros.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

class DynamicObject;

class Map
{
public:
	//c-tors
	Map() = default;
	Map(std::vector<std::string>* map, int height,int width);

	// map functions
	void load_textures();
	void Draw(sf::RenderWindow& main_window);

	// getters
	Player* get_player();
	std::vector<Enemy*> get_enemies();
	std::vector<std::shared_ptr<StaticObject>>* get_static();
	int get_height();
	int get_width();
	int get_coin_size();

	// setters
	void set_objects();

	// info
	bool is_there_ground(sf::Vector2f location);
	bool we_are_hanging_on_rope(sf::Vector2f location_l, sf::Vector2f location_r);
	char what_is_there(sf::Vector2f location);
	bool in_player(sf::Vector2f& location);
	bool out_of_boundrie(sf::Vector2f location);
	bool we_are_on_ladder(sf::Vector2f location);
	int is_on_coin(sf::Vector2f location);
	void delete_coin(int i);
	
private:
	int m_width;
	int m_height;

	char get_char(int i, int j);

	std::vector<std::string> m_map;

	std::vector<std::shared_ptr <sf::Texture>>  m_textures;

	std::vector<std::shared_ptr <StaticObject>> m_static;
	std::vector<std::shared_ptr <StaticObject>> m_ground;
	std::vector<std::shared_ptr <StaticObject>> m_ladders;
	std::vector<std::shared_ptr <StaticObject>> m_poles;

	std::vector<DynamicObject *> m_dynamic;
	std::vector<Consumables*> m_coins;
};