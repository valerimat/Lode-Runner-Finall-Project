#include "State.h"
#include "Settings.h"
#include "Game.h"
#include "MainMenu.h"
#include "InGameMenu.h"
#include "Death.h"
#include "Win.h"

void State::next_main_menu()
{
	State* next;
	next = new MainMenu;
	sate_changed = true;
	next_screen = next;
}
void  State::next_exit()
{
	exit(EXIT_SUCCESS);
}
void  State::next_in_game_menu()
{
	State* next;
	next = new InGameMenu;
	next->set_prev_state(this);
	sate_changed = true;
	next_screen = next;
}
void State::next_death_screen()
{
	State* next;
	next = new Death;
	sate_changed = true;
	next_screen = next;
}
void State::next_game()
{
	State* next;
	next = new Game;
	sate_changed = true;
	next_screen = next;
}
void  State::next_continue()
{
	if (m_previouse_screen != nullptr)
	{
		sate_changed = true;
		next_screen = m_previouse_screen;
	}
}
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

void  State::next_scoreboard()
{
	//State* next;
	//next = new ScoreBoard(this);
	//sate_changed = true;
	//next_screen = next;
}
void  State::next_win(int score)
{
	State* next;
	next = new Win(score);
	sate_changed = true;
	next_screen = next;
}
void  State::next_settings()
{
	State* next;
	next = new Settings(this);
	sate_changed = true;
	next_screen = next;
}