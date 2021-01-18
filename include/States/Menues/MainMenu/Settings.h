#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Selection.h"
#include "Menu.h"
class Button;

class Settings : public Menu
{
public:
	Settings(State* prev);
	void load() override;
	void on_update() override;
	void handle_event(float dt)override;
	bool satate_changed();


private:

	void load_textures();
	void load_buttons();
	void load_background();
	void load_arrow();
	
};
