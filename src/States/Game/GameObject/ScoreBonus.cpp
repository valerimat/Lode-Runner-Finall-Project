#include "ScoreBonus.h"
#include "Score.h"

//=============================================================================
void ScoreBonus::Surprise(Map* map)
{
	Score::GetScore().increase_points();
}
//=============================================================================
