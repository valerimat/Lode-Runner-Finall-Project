#include "MainMenu.h"
#include "Game.h"	

MainMenu::MainMenu()
{
	load_textures();
	load_background();
	load_buttons();
}
void MainMenu::Load() 
{

}
void MainMenu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].Draw(window);
};
void MainMenu::on_update() 
{

};
void MainMenu::handle_event(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		//need to do it based on selected button
		set_next_state(State::Game);
}

Screens* MainMenu::get_next_state()
{
	return next_screen;
}

void  MainMenu::set_next_state(State next)
{
	next_state = next;

	switch (next)
	{
	case State::Main:
		break;
	case State::Game:
		next_screen = new Game;
		break;
	case State::End:
		break;
	default:
		break;
	}
}
bool MainMenu::satate_changed()
{
	if (next_state != base_sate)
		return true;

	return false;
}
void MainMenu::load_textures()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("play_button.png");
	m_textures.push_back(texture);
}

void MainMenu::load_background()

{

}
void MainMenu::load_buttons()
{
	Button play(m_textures[0], sf::Vector2f(300, 300));
	m_buttons.push_back(play);
}