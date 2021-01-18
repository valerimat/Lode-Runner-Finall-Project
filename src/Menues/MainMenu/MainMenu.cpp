#include "MainMenu.h"
#include "Game.h"	
#include "Settings.h"
//========================Ctor
MainMenu::MainMenu()	
{
	my_state = (StateEnum::Main);
	next_state = (StateEnum::Main);
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
	set_prev_state(nullptr);
}

//do we need it?
void MainMenu::Load() 
{

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
//========================States and teyr handeling:



void  MainMenu::set_next_state(ButtonNames next_state)
{	
	State* next;
	switch (next_state)
	{

	case ButtonNames::Play:
		next_game();
		break;
	case ButtonNames::Settings:
		next_settings();
		break;
	case ButtonNames::Scoreboard:
		next_scoreboard();
		break;
	case ButtonNames::Exit:
		next_exit();
		break;
	}
}

/*
Bool that hold if we had a state change
*/
bool MainMenu::satate_changed()
{
	return sate_changed;
}



//========================All loading functions:
/*
Loads all textures
*/
void MainMenu::load_textures()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("play.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("setting_button.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("scoreboard.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("exit_button.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
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
	Button play(m_textures[0], sf::Vector2f(300, 300),ButtonNames::Play);
	m_buttons.push_back(play);

	Button settings(m_textures[1], sf::Vector2f(300, 400),ButtonNames::Settings);
	m_buttons.push_back(settings);

	//Button scoreboard(m_textures[2], sf::Vector2f(300, 500), ButtonNames::Scoreboard);
	//m_buttons.push_back(scoreboard);

	Button exit(m_textures[3], sf::Vector2f(300, 500), ButtonNames::Exit);
	m_buttons.push_back(exit);
}

void MainMenu::load_arrow()
{
	m_arrow = Selection(m_textures[4],sf::Vector2f(250, 300));
}