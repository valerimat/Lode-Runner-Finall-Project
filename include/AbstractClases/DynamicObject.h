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
	//virtual ~DynamicObject() = default;
	DynamicObject(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture);
	using Object::Object;
	virtual void init_object(char  m_name, sf::Vector2f  m_location);
	void Draw(sf::RenderWindow &window);
	void set_texture(std::shared_ptr<sf::Texture> texture);
	void set_sprite();


	sf::Vector2f get_location();
	void update_location(NextStep step,float dt);
	float get_width();
	float get_height();
	sf::Sprite get_sprite();

protected:

	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;
	
};