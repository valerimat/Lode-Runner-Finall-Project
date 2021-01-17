#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "State.h"
#include <vector>
#include "Macros.h"
#include "Selection.h"

class Menu : public State
{
public:
	
	State* get_next_state();

	void set_prev_state(State* prev_screen);
	void Draw(sf::RenderWindow& window) override;

protected:
	sf::Sprite background;

	void check_release();
	void check_preseed_now();

	sf::Keyboard::Key was_pressed;

	int index_of_selected_button = 0;

	std::vector < std::shared_ptr<sf::Texture>> m_textures;

	std::vector <Button> m_buttons;

	Selection m_arrow;
};