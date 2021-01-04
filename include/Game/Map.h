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
	Map() = default;
	Map(std::vector<std::string>* map, int height,int width);
	void load_textures();
	void Draw(sf::RenderWindow &main_window);
	Player* get_player();
	std::vector<StaticObject> * get_static();
	void set_objects();
	std::vector<Enemy *> get_enemies();
	char what_is_there_bellow(sf::Vector2f & location);
	char what_is_there(sf::Vector2f location);
	char collision_top_right(sf::Vector2f& location);
	char get_char(sf::Vector2f  & location);
	bool in_player(sf::Vector2f& location);
	bool out_of_boundrie(sf::Vector2f& location);
	int get_height();
	int get_width();
	bool we_are_centerd(sf::Vector2f& location);
	sf::Vector2f get_bounding_sprt_loc(sf::Vector2f location);

	//checks
	bool is_ground(sf::Vector2f& location);
	bool is_ladder(sf::Vector2f& location);
	bool we_are_hanging_on_rope(sf::Vector2f& location_l , sf::Vector2f& location_r);
private:
	int m_width;
	int m_height;
	char get_char(int i, int j);
	std::vector<std::string> m_map;
	std::vector<std::shared_ptr<sf::Texture>> m_textures;
	std::vector<StaticObject> m_static;
	std::vector<DynamicObject *> m_dynamic;
};