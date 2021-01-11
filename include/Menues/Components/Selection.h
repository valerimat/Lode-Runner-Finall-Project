#pragma once
#include <SFML/Graphics.hpp>

class Selection
{
public:
	Selection()= default;
	Selection(std::shared_ptr<sf::Texture> texture, sf::Vector2f location);
	void Draw(sf::RenderWindow& window);
	void move_arrow(sf::Vector2f location);
private:
	sf::Sprite m_sprite_l;
	sf::Sprite m_sprite_r;
};