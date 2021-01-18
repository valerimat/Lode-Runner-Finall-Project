#include "Score.h"

Score::Score()
{
	m_score = 0;
}

void Score::reset_score()
{
	m_score = 0;
}

int Score::GetPoints()
{
	return m_score;
}
void Score::advance_level()
{
	lvl++;
}
void Score::IncreasePoints()
{
	m_score += lvl * 5;
}