#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Selection.h"
#include "Menu.h"
class Button;

class Win :public Menu
{
public:
	// c-tors
	Win(int score);
	~Win();

	//base functions:
	void load() override;
	void Draw(sf::RenderWindow& window) override;
	void on_update() override;
	void handle_event(float dt)override;

private:
	int m_score;

	sf::Text text;
	sf::Font* font;

	void load_text(int score);
	void load_textures();
	void load_buttons();
	void load_background();
	void load_arrow();
};