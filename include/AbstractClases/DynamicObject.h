#pragma once
#include "Macros.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
class Map;

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

	//Getters:
	sf::Vector2f get_location();
	sf::Sprite get_sprite();

	void update_location(NextStep step,float dt);
	
protected:
	sf::Sprite m_sprite;
	
};