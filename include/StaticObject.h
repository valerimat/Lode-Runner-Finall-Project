#pragma once
#include "Macros.h"
#include "Object.h"
#include <SFML/Graphics.hpp>

class StaticObject : public Object
{
public:
	using Object::Object;
	void Draw(sf::RenderWindow &window);
	void set_texture(std::shared_ptr<sf::Texture> texture);

protected:
	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;

};