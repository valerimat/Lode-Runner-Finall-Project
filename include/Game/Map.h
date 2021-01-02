#pragma once
#include <vector>
#include <string>
#include "StaticObject.h"
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
	Map();
	void load_maps();
	void load_textures();
	void Draw(sf::RenderWindow &main_window);
	Player* get_player();
	std::vector<StaticObject> get_static();
	void set_objects();
	std::vector<Enemy *> get_enemies();
	char what_is_there_bellow(sf::Vector2f & location);
	char what_is_there_on_the_side(sf::Vector2f& location);
	char collision_top_right(sf::Vector2f& location);

private:
	int m_width;
	int m_height;
	char get_char(int i, int j);
	std::vector<std::shared_ptr<sf::Texture>> m_textures;
	std::vector<std::vector<std::string>> m_maps;
	std::vector <std::vector <std::string>> m_maps_clean;
	std::vector<StaticObject> m_static;
	std::vector<DynamicObject *> m_dynamic;
};