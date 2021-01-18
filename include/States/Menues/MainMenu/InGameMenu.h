#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Menu.h"
class Game;
class Button;

class InGameMenu : public Menu
{
public:

	InGameMenu(State* game_stae);
	void load() override;
	void on_update() override;
	void handle_event(float dt)override;


private:

	//state wise:
	void set_prev_state(State* prev_screen);

	//load:
	void load_textures();
	void load_buttons();
	void load_background();
	void load_arrow();
};