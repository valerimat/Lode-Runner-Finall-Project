#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation() = default;

	void SetSprite(sf::Sprite sprite);

private:
	sf::Sprite m_main_sprite;
	sf::IntRect m_rect_sprite;
};