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
	void Draw(sf::RenderWindow& window);

	//Setters:
	void set_sprite(std::shared_ptr<sf::Texture> texture);

	//handle collision:
	void handle_collision(Object& object) override;
	void handle_collision(DynamicObject& object)override;
	void handle_collision(Coin& object) override;
	void handle_collision(Present& object) override;
	void handle_collision(Pole& object) override;
	void handle_collision(Ladder& object) override;
	void handle_collision(StaticObject& object)override;
	void handle_collision(RigidBodyObject& object) override;
	void handle_collision(Player& object) override;
	void handle_collision(Enemy& object) override;

	void gravity(float dt);
	void turn_gravity_on();
	void on_pole(sf::Vector2f  location);
	void move_back(RigidBodyObject& object);

	void Animation(NextStep step, char name);

	//Getters:
	sf::Vector2f get_location();

	void update_location(NextStep step, float dt);
	virtual void on_create() = 0;

	sf::RectangleShape rect;
protected:

	//on create function
	

	sf::Vector2f last_move;

	bool m_gravity;
};