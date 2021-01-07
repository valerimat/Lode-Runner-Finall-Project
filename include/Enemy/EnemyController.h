#pragma once
#include <vector>
#include "MovementController.h"
#include "OneSide.h"
#include "RandomPath.h"
#include "Astar.h"
class Enemy;
class Map;


class EnemyController :public MovementController
{
public:
	//C-tors:
	using MovementController::MovementController;

	//Setters:
	void set_paths();

	//Helpers:
	void move_enemies(float dt);
	bool reached_player(Map* map);
	void init_controller();
private:

	std::vector<Enemy *> m_enemies;
};