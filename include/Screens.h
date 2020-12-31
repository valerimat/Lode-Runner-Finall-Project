#pragma once
#include "Macros.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

class Screens
{
public:
	Screens(Game & game_screen);

	void Draw(sf::RenderWindow &window);
	void set_state(State curr_state);

private:
	State m_state;
	Game * m_game_screen;
	
};