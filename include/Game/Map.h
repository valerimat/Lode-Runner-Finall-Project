#pragma once
#include <vector>
#include <string>
#include "StaticObject.h"
#include "Macros.h"
#include "Player.h"
#include "Enemy.h"
#include "Music.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include "Graph.h"
class Coin;
class Present;
class DynamicObject;

class Map
{
public:
	//c-tors
	Map() = default;
	Map(std::vector<std::string>* map, int height,int width, int timer);

	// map functions
	void LoadTextures();
	void Draw(sf::RenderWindow& main_window);

	// getters
	Player* get_player();
	std::vector<Enemy*> GetEnemies();
	std::vector<std::shared_ptr<StaticObject>>* GetStatic();
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

	// action
	void DeleteCoin(Coin & coin);
	void DeletePresent(Present & present);
	
private:
	int m_width;
	int m_height;
	int m_timer;

	char GetChar(int i, int j);

	Music *m_music = new Music;

	Graph * m_graph;

	std::vector<std::string> m_map;

	std::vector<std::shared_ptr <StaticObject>> m_holes;
	std::vector<std::shared_ptr <StaticObject>> m_holes_to_close;
	std::vector<float> holes_time;

	std::vector<std::shared_ptr <sf::Texture>>  m_textures;

	std::vector<std::shared_ptr <StaticObject>>  m_static;
	std::vector<std::shared_ptr <StaticObject>>  m_coins;
	std::vector<std::shared_ptr <StaticObject>>  m_presents;
	std::vector<std::shared_ptr <DynamicObject>> m_dynamic;
};