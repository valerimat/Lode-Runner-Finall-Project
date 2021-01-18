#include "InGameMenu.h"
#include "Game.h"	
#include "Settings.h"
#include "MainMenu.h"

//C-tor:
InGameMenu::InGameMenu(State * game_stae)
{
	set_prev_state(game_stae);
	load();
}
//=============================================================================

//do we need it?
//=============================================================================
void InGameMenu::load()
{
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
}
//=============================================================================

//=============================================================================
void InGameMenu::on_update()
{

};
//=============================================================================

//Event handeling :
//=============================================================================
void InGameMenu::handle_event(float dt)
{
	check_preseed_now();
	check_release();
}
//=============================================================================

//=============================================================================
void InGameMenu::set_prev_state(State* prev_screen)
{
	m_previouse_screen = prev_screen;
}
//=============================================================================

//========================All loading functions:

//Load:
//=============================================================================
void InGameMenu::load_background()
{
	float scale_height = float(HEIGHT) / 900.f,
		scale_width = float(WIDTH) / 1200.f;

	background.setTexture(*m_textures[6]);
	background.scale(scale_width, scale_height);
}
//=============================================================================

//=============================================================================
void InGameMenu::load_buttons()
{
	Button Continue(m_textures[0], sf::Vector2f(300, 300), States::Continue);
	m_buttons.push_back(Continue);
	
	Button main_menu(m_textures[1], sf::Vector2f(300, 400), States::MainMenu);
	m_buttons.push_back(main_menu);

	Button reset_level(m_textures[2], sf::Vector2f(300, 500), States::ResetLevel);
	m_buttons.push_back(reset_level);

	Button settings(m_textures[3], sf::Vector2f(300, 600), States::Settings);
	m_buttons.push_back(settings);

	Button exit(m_textures[4], sf::Vector2f(300, 700), States::Exit);
	m_buttons.push_back(exit);
}
//=============================================================================

//=============================================================================
void InGameMenu::load_arrow()
{
	m_arrow = Selection(m_textures[5], sf::Vector2f(250, 300));
}
//=============================================================================

//=============================================================================
void InGameMenu::load_textures()
{
	auto texture = new sf::Texture;
	texture->loadFromFile("continue.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("main_menu_png.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("reset_button.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("setting_button.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("exit_button.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("pause.png");
	m_textures.push_back(texture);
}
//=============================================================================