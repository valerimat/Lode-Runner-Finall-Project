#include "LivesBonus.h"

void LivesBonus::Surprise(Map *map)
{
	map->get_player()->add_lives();
}
