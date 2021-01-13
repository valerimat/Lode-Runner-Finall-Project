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
	Enemy(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture, int smart);
	void set_map(Map* map);
	//Setters:
	virtual void set_smartness(int i);
	void set_waypoint();

	//Getters:
	IQ get_iq();

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

	//helpers:
	void move(float dt);
	bool no_waypoints();
	bool checke_if_reached();
	NextStep direction_to_waypoint();
	bool m_falling = false;
private:
	
	Map* m_map;
	Algo * algo;
	std::vector<sf::Vector2f> waypoints;
	sf::Vector2f next_waypoint;
	IQ m_iq;

};