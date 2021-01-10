#include "Button.h"


Button::Button(std::shared_ptr<sf::Texture> texture, sf::Vector2f location)
{
	m_sprite.setTexture(*texture);
	m_sprite.setPosition(location);
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}