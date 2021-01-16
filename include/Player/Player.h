#pragma once
#include <SFML/Graphics.hpp>
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

	using DynamicObject::DynamicObject;

	//Lives* get_lives();

	void delete_left();
	void delete_right();

	//PlayerController * get_controller();
	void Move(sf::Keyboard::Key key,float dt);
	void set_map(Map * map);
	//Handle collision:
	virtual void handle_collision(RigidBodyObject& object) override;
	void handle_collision(Pole& object) override;
	void handle_collision(Coin& object) override;
	void handle_collision(Present& object) override;
	void handle_collision(Ladder& object) override;
	void handle_collision(Object& object) override;
	void handle_collision(StaticObject& object)override;
	void handle_collision(DynamicObject& object)override;
    void handle_collision(Player& object) override;
	void handle_collision(Enemy& object) override;
	bool m_no_ground =false;
private:
	Map* m_map;
	Music* m_music = new Music;
	Lives m_lives;
	bool m_standing;
	
};
