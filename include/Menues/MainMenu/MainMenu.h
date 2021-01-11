#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Selection.h"
#include "Menu.h"
class Button;

class MainMenu : public Menu
{
public:
	MainMenu();
	void Load() override;
	void on_update() override;
	void handle_event(float dt)override;
	void  set_next_state(ButtonNames next_state )override;
	bool satate_changed();
	StateEnum get_state() { return my_state; };

private:

	float stop = 0;
	void load_textures();
	void load_buttons();
	void load_background();
	void load_arrow();
};