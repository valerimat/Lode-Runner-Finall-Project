#pragma once
// include section
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DynamicObject.h"
#include "Lives.h"
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
	
	//Ctors:
	using DynamicObject::DynamicObject;
	Player(char name, sf::Vector2f locaiton, sf::Texture * texture);
	void on_create()override;

	//Setters:
	void set_map(Map* map);


	//For Digging:
	void delete_left();
	void delete_right();
	
	//Move:
	void Move(sf::Keyboard::Key key,float dt);
	

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


	//For lives managment:
	int get_lives();
	void add_lives();


private:
	
	//for diggind:
	sf::Vector2f BottomRight();
	sf::Vector2f BottomLeft();

	//Mebers:
	Map* m_map;
	Lives m_lives;
	bool m_standing;
	
};

