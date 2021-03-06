#pragma once
#include <vector>
#include "MovementController.h"
#include "OneSide.h"
#include "RandomPath.h"
class Enemy;
class Map;


class EnemyController :public MovementController
{
public:
	// c-tors:
	using MovementController::MovementController;

	// setters:
	void set_path();

	// helpers:
	void move(float dt) override;
	void init_controller() override;

private:

	// private functions
	void move_enemy(float dt, Enemy& enemy);
	void apply_gravity(float dt, Enemy& enemy);
	bool enemy_falling(sf::Vector2f before, sf::Vector2f after);
	void set_curr_location();
	void set_previous_location();
	void check_stuck();

	// private members
	std::vector<sf::Vector2f> prev_loc;
	std::vector<sf::Vector2f> curr_loc;

	std::vector<Enemy*> m_enemies;
};