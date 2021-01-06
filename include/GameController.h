#pragma once
#include "Macros.h"
#include "Screens.h"
#include "Map.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "PlayerController.h"
#include "EnemyController.h"
#include <chrono>

namespace GameController
{
	void Run();
	void calculate_valid_steps(EnemyController & enemy_cont, PlayerController & player_cont);
	void move_g(EnemyController & enemy_cont, PlayerController & player_cont, float dt, sf::Keyboard::Key keypress);
};