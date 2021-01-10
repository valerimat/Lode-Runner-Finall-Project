#pragma once
#include "Screens.h"
#include <SFML/Graphics.hpp>
#include "Button.h"

class MainMenu :public Screens
{
public:
	MainMenu();
	void Load() override;
	void Draw(sf::RenderWindow& window) override;
	void on_update() override;
	void handle_event(sf::Keyboard::Key, float dt)override;
private:
	void load_textures();
	void load_buttons();
	void load_background();
	std::vector<Button> m_buttons;
	std::vector < std::shared_ptr<sf::Texture>> m_textures;
};