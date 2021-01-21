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

	~Menu();
	void Draw(sf::RenderWindow& window) override;

protected:

	//members:
	sf::Sprite background;
	sf::Keyboard::Key was_pressed;
	int index_of_selected_button = 0;
	std::vector<sf::Texture*> m_textures;
	std::vector <Button> m_buttons;
	Selection m_arrow;

	//functions:
	virtual void check_release();
	virtual void check_preseed_now();
	
};