#include "Player.h"

void Player::move(sf::Keyboard::Key key,float dt)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		update_location(NextStep::LEFT,dt);
		break;
	case sf::Keyboard::Right:
		update_location(NextStep::RIGHT,dt);
		break;
	case sf::Keyboard::Up:
		update_location(NextStep::UP,dt);
		break;
	case sf::Keyboard::Down:
		update_location(NextStep::DOWN,dt);
		break;
	default:
		break;
	}

	m_sprite.setPosition(m_location);
}


void Player::set_valid(std::vector <NextStep> valid_steps)
{
	m_valid_steps = valid_steps;

	if (m_valid_steps.size() == 0)
		m_valid_steps.push_back(NextStep::NONE);
}


std::vector <NextStep> Player::get_valid()
{
	return m_valid_steps;
}