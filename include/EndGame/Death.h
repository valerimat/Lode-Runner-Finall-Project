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
		void Load() override;
		void Draw(sf::RenderWindow& window) override;
		void on_update() override;
		void handle_event(float dt)override;

		

		//states:
		void set_prev_state(State* state);
		State* get_next_state()override;
		void set_next_state(ButtonNames  screen) override;
		bool satate_changed();
		StateEnum get_state() { return StateEnum::Game; };


	private:
		sf::Sprite wasted;
		void load_textures();
		void load_buttons();
		void load_background();
		void load_arrow();
};