#pragma once
#include "Macros.h"
#include "State.h"
#include "Map.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PlayerController.h"
#include "EnemyController.h"
#include <chrono>
#include "MainMenu.h"

namespace GameController
{
	void Run();
	void OnUpdate(std::chrono::steady_clock::time_point& last, State*& screen);
};