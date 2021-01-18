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
	void load() override;
	void on_update() override;
	void handle_event(float dt)override;


private:
	sf::Keyboard::Key was_pressed;

	void load_textures();
	void load_buttons();
	void load_background();
	void load_arrow();
};