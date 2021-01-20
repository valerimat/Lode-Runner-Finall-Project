#pragma once
#include "DynamicObject.h"
#include "Macros.h"
class StaticObject;
class Object;
class Player;
class Ladder;
class Pole;
class Coin;
class Present;
class Algo;

class Enemy : public DynamicObject
{
public:
	//C-tors:
	using DynamicObject::DynamicObject;
	Enemy(char name, sf::Vector2f locaiton, sf::Texture* texture);

	void set_map(Map* map);
	//Setters:
	virtual void set_smartness(int i);
	void set_waypoints();
	void reset_path();

	//Getters:
	IQ get_IQ();
	sf::Vector2f get_center();
	//collisions:
	void handle_collision(Pole& object) override;
	void handle_collision(Ladder& object) override;
	void handle_collision(Coin& object) override ;
	void handle_collision(Present& object) override;
	void handle_collision(RigidBodyObject& object) override;
	void handle_collision(Object& object) override ;
	void handle_collision(StaticObject& object)override;
	void handle_collision(Player& object) override ;
	void handle_collision(Enemy& object) override ;
	void handle_collision(DynamicObject& object) override;

	//for debug !!
	
	bool is_in_hole();
	void up_stuck();
	void reset_stuck();
	bool stuck();
	void dont_move();

	//helpers:
	void move(float dt);
	bool no_waypoints();
	bool check_reached();
	NextStep direction_to_waypoints();
	bool m_falling = false;
	void on_create()override;
	
private:
	
	void set_next_waypoints();
	
	bool m_in_hole = false;
	int stuck_counter = 0;
	int m;
	Map* m_map;
	Algo * algo;
	std::vector<sf::Vector2f> waypoints;
	sf::Vector2f next_waypoint = sf::Vector2f(-1, -1);
	IQ m_iq;

};