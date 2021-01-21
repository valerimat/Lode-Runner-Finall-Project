#include "TimeBonus.h"

void TimeBonus::Surprise(Map *map)
{
	int* timer = map->get_timer();
	*timer += 5;
}