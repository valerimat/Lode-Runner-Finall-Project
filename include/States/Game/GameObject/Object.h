#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>
class DynamicObject;
class Enemy;
class StaticObject;
class RigidBodyObject;
class Player;
class Enemy;
class Ladder;
class Pole;
class Present;
class Coin;

class Object
{
public:

	//C-tor
	Object(char m_name, sf::Vector2f m_location);

	//Dtor
	virtual ~Object() = default;

	//Getters:
	char		 get_name();
	sf::Vector2f get_location();
	sf::Sprite &  get_sprite();

	//coliisions
	virtual void handle_collision(Object & object) = 0;

	virtual void handle_collision(Present& object) = 0;
	virtual void handle_collision(Coin& object) = 0;

	virtual void handle_collision(StaticObject& object) = 0;
	virtual void handle_collision(Pole & object) = 0;
	virtual void handle_collision(RigidBodyObject& object) = 0;
	virtual void handle_collision(Ladder& object) =0;

	virtual void handle_collision(DynamicObject& object) = 0;
	virtual void handle_collision(Player& object) = 0;
	virtual void handle_collision(Enemy& object) = 0;

	//Setters:
	void set_name(char & name);
	void SetLocation(sf::Vector2f  location);

protected:

	sf::Sprite m_sprite;
	char m_name;
};