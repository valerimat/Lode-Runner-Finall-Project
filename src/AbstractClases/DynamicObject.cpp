#include "DynamicObject.h"
#include "Map.h"

DynamicObject::DynamicObject(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture):
	Object(name, locaiton)
{
	//set_sprite(texture);
}

void DynamicObject::set_texture(std::shared_ptr<sf::Texture> texture)
{
	m_texture = texture;
	set_sprite();
}

void DynamicObject::set_sprite()
{
	sf::Sprite sprite;
	sprite.setTexture(*m_texture);
	m_location.y += 50;
	sprite.setPosition(m_location);
	sprite.setScale(sf::Vector2f(0.8, 0.8));
	m_sprite = sprite;
}

sf::Vector2f DynamicObject::get_location()
{
	return m_sprite.getPosition();
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



void DynamicObject::update_location(NextStep step,float dt)
{
	switch (step)
	{
	case NextStep::LEFT:
		m_sprite.move(dt *sf::Vector2f(-STEP, 0));
		m_location.x -= STEP;
		break;
	case NextStep::RIGHT:
		m_sprite.move(dt *sf::Vector2f(STEP, 0));
		m_location.x += STEP;
		break;
	case NextStep::UP:
		m_sprite.move(dt *sf::Vector2f(0,-STEP));
		m_location.y -= STEP;
		break;
	case NextStep::DOWN:
		m_sprite.move(dt * sf::Vector2f(0, STEP));
		m_location.y += STEP;
		break;
	default:
		break;
	}
}


float DynamicObject::get_width()
{
	return m_sprite.getGlobalBounds().width;
}
float DynamicObject::get_height()
{
	return m_sprite.getGlobalBounds().height;
}

sf::Sprite DynamicObject::get_sprite()
{
	return m_sprite;
}
