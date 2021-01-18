#include "Death.h"
#include "Game.h"	
#include "Settings.h"
#include "MainMenu.h"

//=============================================================================
Death::Death()
{
	load();
}
//=============================================================================

//=============================================================================
void Death::load()
{
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
}
//=============================================================================

//=============================================================================
void Death::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].Draw(window);

	m_arrow.Draw(window);

	window.draw(background);
}
//=============================================================================

//=============================================================================
void Death::on_update()
{
	
}
//=============================================================================

//=============================================================================
void Death::handle_event(float dt)
{

	check_preseed_now();
	check_release();

}
//=============================================================================

//=============================================================================
void Death::load_background()
{
	
}

void Death::load_buttons()
{
	Button play(m_textures[0], sf::Vector2f(300, 300), States::Play);
	m_buttons.push_back(play);

	Button main(m_textures[1], sf::Vector2f(300, 400), States::MainMenu);
	m_buttons.push_back(main);

	Button settings(m_textures[2], sf::Vector2f(300, 500), States::Exit);
	m_buttons.push_back(settings);
}

void Death::load_arrow()
{
	m_arrow = Selection(m_textures[3], sf::Vector2f(250, 300));
}

void Death::load_textures()
{


	//MAIN MENU BUTTON
	auto texture = new sf::Texture;
	texture->loadFromFile("play_button.png");
	m_textures.push_back(texture);

	
	texture = new sf::Texture;
	texture->loadFromFile("main_menu_png.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("exit_button.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);


	
}
