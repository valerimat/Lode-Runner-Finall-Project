#pragma once
#include "Map.h"
#include <vector>
#include "MovementController.h"
#include "Enemy.h"
#include "Algorithms.h"
#include "OneSide.h"
#include "RandomPath.h"
#include "Astar.h"


class EnemyController :public MovementController
{
public:
	EnemyController(Map & map);
	void move_enemies(Map * map);
	bool reached_player(Map* map);
private:
	int m_num_of_enemies;
	int m_loop_counter;
	int m_curr_counter;

	std::vector<Enemy *> m_enemies;
};