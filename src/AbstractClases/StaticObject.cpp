#include "StaticObject.h"

StaticObject::StaticObject(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture):
Object(name,locaiton)
{
	set_sprite(texture);
}
//-----------------------------------------------------------------------------

void StaticObject::set_sprite(std::shared_ptr<sf::Texture> texture)
{
	sf::Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setPosition(m_location);
	sprite.setScale(sf::Vector2f(0.8, 0.8));
	m_sprite = sprite;
}
//-----------------------------------------------------------------------------

sf::Sprite& StaticObject::get_sprite()
{
	return m_sprite;
}
//-----------------------------------------------------------------------------

void StaticObject::Draw(sf::RenderWindow & main_window)
{
	main_window.draw(m_sprite);
}
//-----------------------------------------------------------------------------

bool StaticObject::in_bounds(sf::Vector2f &location)
{
	if (m_sprite.getGlobalBounds().contains(location))
	{	
		return true;
	}	
	return false;
}
//-----------------------------------------------------------------------------

bool StaticObject::in_bounds(sf::RectangleShape& rect)
{
	if (m_sprite.getGlobalBounds().intersects(rect.getGlobalBounds()))
		return true;
	return false;
}
//-----------------------------------------------------------------------------