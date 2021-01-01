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
	void set_sprite();
	sf::Sprite& get_sprite();
	bool in_bounds(sf::Vector2f &location);

protected:

	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;
};