#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"
#include "Lives.h"
#include "PlayerController.h"
#include <vector>
#include "Macros.h"
class Map;
class Coin;
class Present;
class Pole;
class Ladder;
class RigidBodyObject;


class Player : public DynamicObject
{
public:

	//using DynamicObject::DynamicObject;
	Player(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture);
	//Lives* get_lives();

	void DeleteLeft();
	void DeleteRight();

	//PlayerController * get_controller();
	void Move(sf::Keyboard::Key key,float dt);
	void SetMap(Map * map);
	//Handle collision:
	void handle_collision(RigidBodyObject& object) override;
	void handle_collision(Pole& object) override;
	void handle_collision(Coin& object) override;
	void handle_collision(Present& object) override;
	void handle_collision(Ladder& object) override;
	void handle_collision(Object& object) override;
	void handle_collision(StaticObject& object)override;
	void handle_collision(DynamicObject& object)override;
    void handle_collision(Player& object) override;
	void handle_collision(Enemy& object) override;

	
	void on_create()override;
	int GetLives();
	void AddLives();

private:
	
	Map* m_map;
	Lives m_lives;
	bool m_standing;
	
};
