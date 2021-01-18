#include "MainMenu.h"
#include "Game.h"	
#include "Settings.h"
//========================Ctor
MainMenu::MainMenu()	
{
	load();
}

//do we need it?
void MainMenu::load()
{
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
}
//========================Base functions:


void MainMenu::on_update()
{

};

//========================Event handeling - need to be fixed
void MainMenu::handle_event(float dt)
{

	check_preseed_now();
	check_release();
}


//========================All loading functions:
/*
Loads all textures
*/
void MainMenu::load_textures()
{
	sf::Texture * texture = new sf::Texture;
	texture->loadFromFile("play.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("setting_button.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("scoreboard.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("exit_button.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("background_main.png");
	m_textures.push_back(texture);

	
}

void MainMenu::load_background()
{

	float scale_height = float(HEIGHT)/900.f,
		scale_width = float(WIDTH)/1200.f;

	background.setTexture(*m_textures[5]);
	background.scale(scale_width, scale_height);

}

void MainMenu::load_buttons()
{
	Button play(m_textures[0], sf::Vector2f(300, 300),States::Play);
	m_buttons.push_back(play);

	Button settings(m_textures[1], sf::Vector2f(300, 400),States::Settings);
	m_buttons.push_back(settings);

	//Button scoreboard(m_textures[2], sf::Vector2f(300, 500), ButtonNames::Scoreboard);
	//m_buttons.push_back(scoreboard);

	Button exit(m_textures[3], sf::Vector2f(300, 500), States::Exit);
	m_buttons.push_back(exit);
}

void MainMenu::load_arrow()
{
	m_arrow = Selection(m_textures[4],sf::Vector2f(250, 300));
}