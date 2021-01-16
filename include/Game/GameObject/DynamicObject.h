#pragma once
#include "Macros.h"
#include "Object.h"
#include "Clock.h"
#include <SFML/Graphics.hpp>
class Map;
class RigidBodyObject;

/*
Will hold any object that can move
*/
class DynamicObject : public Object
{
public:
	//Ctors:
	using Object::Object;
	DynamicObject(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture);
	
	//Draw:
	void Draw(sf::RenderWindow &window);
	
	//Setters:
	void set_sprite(std::shared_ptr<sf::Texture> texture);

	//handle collision:
	virtual void handle_collision(Object& object) override;
	void gravity(float dt);
	void turn_gravity_on();
	void on_pole(sf::Vector2f  location);
	void move_back();

	void Animation(NextStep step, char name);

	//Getters:
	sf::Vector2f get_location();

	void update_location(NextStep step,float dt);
	
protected:
	sf::Vector2f last_move;
	bool m_gravity;
};