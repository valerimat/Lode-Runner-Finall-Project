#include "StaticObject.h"


void StaticObject::set_texture(std::shared_ptr<sf::Texture> texture)
{
	m_texture = texture;
}

void StaticObject::Draw(sf::RenderWindow & main_window)
{
	main_window.draw(m_sprite);
}