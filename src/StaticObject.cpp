#include "StaticObject.h"


void StaticObject::set_texture(std::shared_ptr<sf::Texture> texture)
{
	m_texture = texture;
	set_sprite();
}
void StaticObject::set_sprite()
{
	sf::Sprite sprite;
	sprite.setTexture(*m_texture);
	sprite.setPosition(get_location());
	sprite.setScale(sf::Vector2f(0.8, 0.8));
	m_sprite = sprite;
}

sf::Sprite& StaticObject::get_sprite()
{
	return m_sprite;
}

void StaticObject::Draw(sf::RenderWindow & main_window)
{
	main_window.draw(m_sprite);
}