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
	void SetPaths();

	//Helpers:
	void MoveEnemies(float dt);
	void InitController();
private:
	void MoveEnemy(float dt, Enemy* enemy);
	void ApplyGravity(float dt, Enemy* enemy);
	bool EnemyFalling(sf::Vector2f before, sf::Vector2f after);
	void SetCurrLocation();
	void SetPreviousLocations();
	void CheckStuck();

	std::vector<sf::Vector2f> prev_loc;
	std::vector<sf::Vector2f> curr_loc;

	std::vector<Enemy *> m_enemies;
};