#include "Selection.h"




Selection::Selection(std::shared_ptr<sf::Texture> texture, sf::Vector2f location)
{
	m_sprite_l.setPosition(location);
	m_sprite_l.setTexture(*texture);

	
	m_sprite_r.setTexture(*texture);
	m_sprite_r.scale(-1, 1);
	m_sprite_r.setPosition(location + sf::Vector2f(300,0));



}
void Selection::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite_l);
	window.draw(m_sprite_r);
}

void Selection::move_arrow(sf::Vector2f  location)
{
	auto base_pos_x_l = m_sprite_l.getPosition().x;
	auto base_pos_x_r = m_sprite_r.getPosition().x;
	m_sprite_l.setPosition(sf::Vector2f(base_pos_x_l, location.y));
	m_sprite_r.setPosition(sf::Vector2f(base_pos_x_r, location.y));
}