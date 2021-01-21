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


	void on_create()override;
	void set_map(Map* map);
	//Setters:
	virtual void set_smartness(int i);
	void set_waypoints();
	void reset_path();

	//Getters:

	IQ get_IQ();
  
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


	//For unstucking:
	void up_stuck();
	void reset_stuck();
	bool stuck();

	//helpers:
	void move(float dt);
	bool no_waypoints();
	bool check_reached();
	virtual void reset_after_hole() override;

	//for falling 
	bool get_m_falling();
	void set_m_falling(bool state);


	
private:
	bool m_falling = false;

	sf::Vector2f get_center();
	NextStep DirectionToWaypoint();
	

	void set_next_waypoints();
	int stuck_counter = 0;

	//to request information
	Map* m_map;

	//for Algorithm
	IQ m_iq;
	Algo * algo;

	std::vector<sf::Vector2f> waypoints;
	sf::Vector2f next_waypoint = sf::Vector2f(-1, -1);
	

};