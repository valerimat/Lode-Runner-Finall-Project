#pragma once
#include "Macros.h"
#include "MainMenu.h"
#include "Game.h"
#include "EndGame.h"


class Screens
{
public:
	void draw(sf::RenderWindow &window);

private:

	State m_state;

	MainMenu m_main_menu;
	Game m_game;
	EndGame m_end_game;

};