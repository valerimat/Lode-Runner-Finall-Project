#include "Present.h"
#include "LivesBonus.h"
#include "TimeBonus.h"
#include "ScoreBonus.h"
#include "EnemyBonus.h"

//=============================================================================
Present::Present(char Name, sf::Vector2f locaiton, sf::Texture * texture)
	:StaticObject(Name, locaiton, texture)
{
	m_type = rand() % 4;

	switch (m_type)
	{
	case 0:
		m_bonus = new LivesBonus;
		break;
	case 1:
		m_bonus = new TimeBonus;
		break;
	case 2:
		m_bonus = new ScoreBonus;
		break;
	case 3:
		m_bonus = new EnemyBonus;
		break;
	}
}
//=============================================================================

//=============================================================================
void Present::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Present::handle_collision(Player& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void Present::handle_collision(Enemy& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
int Present::get_type()
{
	return m_type;
}
//=============================================================================

Bonus* Present::get_bonus()
{
	return m_bonus;
}
//=============================================================================
