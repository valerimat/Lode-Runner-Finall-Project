#include "Screens.h"

//for now has only game screen
Screens::Screens(Game &game_screen) :
	m_game_screen(&game_screen), m_state(State::Game)
{}
//-----------------------------------------------------------------------------

void Screens::set_state(State curr_state)
{
	m_state = curr_state;
}
//-----------------------------------------------------------------------------

void Screens::Draw(sf::RenderWindow &window)
{
	m_game_screen->Draw(window);
}
//-----------------------------------------------------------------------------