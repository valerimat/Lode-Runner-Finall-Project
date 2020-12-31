#pragma once
#include "Macros.h"


class Entity
{
public:
	Entity(sf::Texture& texture);
	void draw(sf::RenderWindow& window);
	sf::Vector2f get_location();

protected:
	sf::Sprite * m_sprite;
	sf::Vector2f location;

};