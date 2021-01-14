#include "Score.h"

Score::Score()
{
	m_score = 0;
}

int Score::GetPoints()
{
	return m_score;
}

void Score::IncreasePoints(int lvl)
{
	m_score += lvl * 5;
}