#pragma once
#include "Screens.h"
#include <SFML/Graphics.hpp>
#include "Button.h"
class Game;

class MainMenu :public Screens
{
public:
	MainMenu();
	void Load() override;
	void Draw(sf::RenderWindow& window) override;
	void on_update() override;
	void handle_event(float dt)override;
	Screens* get_next_state()override;
	void set_next_state(State next) override;
	bool satate_changed();
private:
	State base_sate = State::Main;
	State next_state = State::Main;
	void load_textures();
	void load_buttons();
	void load_background();
	std::vector<Button> m_buttons;
	std::vector < std::shared_ptr<sf::Texture>> m_textures;
};