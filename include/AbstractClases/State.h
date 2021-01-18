#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

class State
{
public:
	State() = default;
	virtual void on_update() = 0;
	virtual void Load() = 0;
	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void handle_event(float dt) = 0;
	virtual void set_next_state(ButtonNames next) = 0;
	virtual State* get_next_state() = 0;
	virtual bool satate_changed() = 0;
	virtual StateEnum get_state() = 0;
	virtual void set_prev_state(State* prev_screen) = 0;

protected:

	void next_main_menu();
	void next_exit();
	void next_in_game_menu();
	void next_reset_level();
	void next_continue();
	void next_scoreboard();
	void next_settings();
	void next_death_screen();
	void next_game();
	void next_win(int score);

	StateEnum my_state;
	StateEnum next_state;
	bool sate_changed = false;
	State* next_screen;
	State* m_previouse_screen;
};