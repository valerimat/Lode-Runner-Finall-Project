#pragma once
#include <vector>
#include <string>
#include "StaticObject.h"
#include "Consumables.h"
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
	void LoadTextures();
	void Draw(sf::RenderWindow& main_window);

	// getters
	Player* GetPlayer();
	std::vector<Enemy*> GetEnemies();
	std::vector<std::shared_ptr<StaticObject>>* GetStatic();
	int GetHeight();
	int GetWidth();

	// setters
	void SetObjects();

	// info
	char WhatIsThere(sf::Vector2f location);
	bool IsOnGround(sf::Vector2f location);
	bool IsOnRope(sf::Vector2f location_l, sf::Vector2f location_r);
	bool IsOnPlayer(sf::Vector2f& location);
	bool IsOnLadder(sf::Vector2f location);
	int  IsOnCoin(sf::Vector2f location);

	// action
	void DeleteCoin(int i);
	
private:
	int m_width;
	int m_height;

	char GetChar(int i, int j);

	std::vector<std::string> m_map;

	std::vector<std::shared_ptr <sf::Texture>>  m_textures;

	std::vector<std::shared_ptr <StaticObject>> m_static;
	std::vector<std::shared_ptr <StaticObject>> m_ground;
	std::vector<std::shared_ptr <StaticObject>> m_ladders;
	std::vector<std::shared_ptr <StaticObject>> m_poles;
	std::vector<std::shared_ptr <StaticObject>> m_coins;
	std::vector<std::shared_ptr <DynamicObject>> m_dynamic;
};