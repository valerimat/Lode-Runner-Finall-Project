#include "DynamicObject.h"

void DynamicObject::set_texture(std::shared_ptr<sf::Texture> texture)
{
	m_texture = texture;
	set_sprite();
}

void DynamicObject::set_sprite()
{
	sf::Sprite sprite;
	sprite.setTexture(*m_texture);
	sprite.setPosition(m_location);
	sprite.setScale(sf::Vector2f(0.8, 0.8));
	m_sprite = sprite;
}
sf::Vector2f DynamicObject::get_location()
{
	return m_location;
}

void DynamicObject::init_object(char  m_name, sf::Vector2f  m_location)
{
	set_name(m_name);
	sf::Vector2f loc(m_location.y * OFFSET, m_location.x * OFFSET);
	set_location(loc);
}

void DynamicObject::Draw(sf::RenderWindow &main_window)
{
	main_window.draw(m_sprite);
}

bool DynamicObject::in_bounds(sf::Vector2f & location)
{
	if (m_sprite.getGlobalBounds().contains(location))
		return true;

	return false;
}

void DynamicObject::update_location(NextStep step)
{
	switch (step)
	{
	case NextStep::LEFT:
		m_location.x -= 10;
		break;
	case NextStep::RIGHT:
		m_location.x += 10;
		break;
	case NextStep::UP:
		m_location.y -= 10;
		break;
	case NextStep::DOWN:
		m_location.y += 10;
		break;
	default:
		break;
	}
}