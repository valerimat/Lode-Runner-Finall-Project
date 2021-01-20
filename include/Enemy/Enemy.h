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
	void SetMap(Map* map);
	//Setters:
	virtual void set_smartness(int i);
	void set_waypoints();
	void reset_path();

	//Getters:

	IQ GetIQ();
  
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
	void UpStuck();
	void ResetStuck();
	bool Stuck();

	//helpers:
	void move(float dt);
	bool NoWaypoints();
	bool CheckIfReached();

	//NEEDDDDDDDDDDD TO FIXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	bool m_falling = false;
	
private:

	sf::Vector2f GetCenter();
	NextStep DirectionToWaypoint();
	

	void SetNextWaypoint();
	int stuck_counter = 0;

	//to request information
	Map* m_map;

	//for Algorithm
	IQ m_iq;
	Algo * algo;

	std::vector<sf::Vector2f> waypoints;
	sf::Vector2f next_waypoint = sf::Vector2f(-1, -1);
	

};