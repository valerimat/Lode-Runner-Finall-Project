#include "Player.h"

void Player::move(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		update_location(NextStep::LEFT);
		break;
	case sf::Keyboard::Right:
		update_location(NextStep::RIGHT);
		break;
	case sf::Keyboard::Up:
		update_location(NextStep::UP);
		break;
	case sf::Keyboard::Down:
		update_location(NextStep::DOWN);
		break;
	default:
		break;
	}

	m_sprite.setPosition(m_location);
}