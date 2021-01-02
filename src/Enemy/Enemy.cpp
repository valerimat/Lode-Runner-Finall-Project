#include "Enemy.h"




IQ Enemy::get_iq()
{
	return m_iq;
}

void Enemy::set_path(std::vector<NextStep> steps)
{
	m_path = steps;
}

void Enemy::move()
{
	NextStep step = m_path[0];
	m_path.erase(m_path.begin());

	switch (step)
	{
	case NextStep::LEFT:
		update_location(NextStep::LEFT);
		break;
	case NextStep::RIGHT:
		update_location(NextStep::RIGHT);
		break;
	case NextStep::UP:
		update_location(NextStep::UP);
		break;
	case NextStep::DOWN:
		update_location(NextStep::DOWN);
		break;

	default:
		break;
	}

	m_sprite.setPosition(m_location);
}


void Enemy::set_smartness()
{
	int random = rand() % 3;

	m_iq = IQ(random);

}
