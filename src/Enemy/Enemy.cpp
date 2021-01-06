#include "Enemy.h"

//Getter:
IQ Enemy::get_iq()
{
	return m_iq;
}
//-----------------------------------------------------------------------------

//Setter:
void Enemy::set_path(std::vector<NextStep> steps)
{
	m_path = steps;
}
//-----------------------------------------------------------------------------
void Enemy::set_smartness(int i)
{
	m_iq = IQ(i);
}
//-----------------------------------------------------------------------------

void Enemy::move(float dt)
{
	NextStep step = m_path[0];

	if (m_path.size() == 1)
		m_path.clear();
	else
	m_path.erase(m_path.begin());
	
	switch (step)
	{
	case NextStep::LEFT:
		update_location(NextStep::LEFT,dt);
		break;
	case NextStep::RIGHT:
		update_location(NextStep::RIGHT,dt);
		break;
	case NextStep::UP:
		update_location(NextStep::UP,dt);
		break;
	case NextStep::DOWN:
		update_location(NextStep::DOWN,dt);
		break;
	case NextStep::NONE:
		break;
	default:
		break;
	}

	m_sprite.setPosition(m_location);
}
//-----------------------------------------------------------------------------


bool Enemy::path_is_empty()
{
	if (m_path.size() == 0)
		return true;

	return false;
}
//-----------------------------------------------------------------------------


