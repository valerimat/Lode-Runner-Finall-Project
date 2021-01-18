#include "Button.h"
#include "State.h"
#include "MainMenu.h"
#include "Settings.h"
#include "Game.h"

Button::Button(std::shared_ptr<sf::Texture> texture, sf::Vector2f location, States name)
{
	m_sprite.setTexture(*texture);
	m_sprite.setPosition(location);
	m_name = name;
}
Button::Button(sf::Texture * texture, sf::Vector2f location, States name)
{
	m_sprite.setTexture(*texture);
	m_sprite.setPosition(location);
	m_name = name;
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::Vector2f Button::get_location()
{
	return m_sprite.getPosition();
}

States Button::get_name()
{
	return m_name;
}