#include "State.h"
#include "Settings.h"
#include "Game.h"
#include "MainMenu.h"
#include "InGameMenu.h"
#include "Death.h"
#include "Win.h"
#include "Score.h"

//=============================================================================
void  State::set_next_state(States next_state)
{

	switch (next_state)
	{
	case States::Win:
		next_win();
		break;
	case States::InGameMenu:
		next_in_game_menu();
		break;
	case States::MainMenu:
		next_main_menu();
		break;
	case States::Play:
		next_game();
		break;
	case States::Death:
		next_death_screen();
		break;
	case States::Exit:
		next_exit();
		break;
	case States::Continue:
		next_continue();
		break;
	case States::Settings:
		next_settings();
		break;
	case States::ResetLevel:
		next_reset_level();
		break;
	case States::Scoreboard:
		next_scoreboard();
		break;
	default:
		break;
	}
}
//=============================================================================

//=======================================STATE DISPATCH========================
void State::next_main_menu()
{
	State* next;
	next = new MainMenu;
	sate_changed = true;
	next_screen = next;
}
//=============================================================================

//=============================================================================
void  State::next_exit()
{
	exit(EXIT_SUCCESS);
}
//=============================================================================

//=============================================================================
void  State::next_in_game_menu()
{
	State* next;
	next = new InGameMenu(this);
	sate_changed = true;
	next_screen = next;
}
//=============================================================================

//=============================================================================
void State::next_death_screen()
{
	State* next;
	next = new Death;
	sate_changed = true;
	next_screen = next;
}
//=============================================================================

//=============================================================================
void State::next_game()
{
	State* next;
	next = new Game;
	sate_changed = true;
	next_screen = next;
}
//=============================================================================

//=============================================================================
void  State::next_continue()
{
	if (m_previouse_screen != nullptr)
	{
		sate_changed = true;
		next_screen = m_previouse_screen;
	}
}
//=============================================================================

//=============================================================================
void  State::next_reset_level()
{
	State* next;
	next = m_previouse_screen;

	//the sattic cast is for safety!!!
	if (static_cast<Game*>(m_previouse_screen))
	{
		static_cast<Game*>(m_previouse_screen)->reset_level();
		sate_changed = true;
		next_screen = next;
	}
}
//=============================================================================

//=============================================================================
void  State::next_scoreboard()
{

}
//=============================================================================

//=============================================================================
void  State::next_win()
{
	auto score = &Score::GetScore();
	State* next;
	next = new Win(score->get_points());
	sate_changed = true;
	next_screen = next;
}
//=============================================================================

//=============================================================================
void  State::next_settings()
{
	State* next;
	next = new Settings(this);
	sate_changed = true;
	next_screen = next;
}
//=============================================================================

//=============================================================================
bool State::satate_changed()
{
	return sate_changed;
}
//=============================================================================

//=============================================================================
State* State::get_next_state()
{
	sate_changed = false;
	return next_screen;
}
//=============================================================================