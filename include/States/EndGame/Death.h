#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Selection.h"
#include "Menu.h"
class Button;

class Death :public Menu
{
	public:
		// c-tors
		Death();

		//base functions:
		void load() override;
		void Draw(sf::RenderWindow& window) override;
		void on_update() override;
		void handle_event(float dt)override;

		//states:

	private:
		
		void load_textures();
		void load_buttons();
		void load_background();
		void load_arrow();
};