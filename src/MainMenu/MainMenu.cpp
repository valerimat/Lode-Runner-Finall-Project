#include "MainMenu.h"

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
void MainMenu::handle_event(sf::Keyboard::Key, float dt)
{

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