#pragma once
#include <vector>
#include <string>
#include "StaticObject.h"
#include "DinamicObject.h"
#include "Macros.h"
#include <SFML/Graphics.hpp>

class Map
{
public:
	Map();
	void load_maps();
	void load_textures();
	void Draw(sf::RenderWindow &main_window);
	void set_objects();

private:
	int m_width;
	int m_height;

	std::vector<std::shared_ptr<sf::Texture>> m_textures;
	std::vector<std::vector<std::string>> m_maps;
	std::vector <std::vector <std::string>> m_maps_clean;
	std::vector<StaticObject> m_static;
	std::vector<DinamicObject> m_dinamic;

};