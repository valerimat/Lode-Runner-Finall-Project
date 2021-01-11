#pragma once
#include <SFML/Graphics.hpp>
#include "Macros.h"

class State;

class Button
{
public:
	Button(std::shared_ptr<sf::Texture> texture, sf::Vector2f location, ButtonNames name);

	void Draw(sf::RenderWindow& window);

	sf::Vector2f get_location();

	ButtonNames get_name();

private:
	ButtonNames m_name;
	sf::Sprite m_sprite;
};