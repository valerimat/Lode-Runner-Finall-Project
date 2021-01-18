#include "InGameMenu.h"
#include "Game.h"	
#include "Settings.h"
#include "MainMenu.h"

//========================Ctor
InGameMenu::InGameMenu()
{
	my_state = (StateEnum::Game);
	next_state = (StateEnum::Game);
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
	set_prev_state(nullptr);
}

//do we need it?
void InGameMenu::Load()
{

}
//========================Base functions:


void InGameMenu::on_update()
{

};

//========================Event handeling - need to be fixed
void InGameMenu::handle_event(float dt)
{
	check_preseed_now();
	check_release();
}
//========================States and teyr handeling:



void  InGameMenu::set_next_state(ButtonNames next_state)
{
	State* next;
	switch (next_state)
	{
	case ButtonNames::Continue:
		next_continue();
		break;
	case ButtonNames::Settings:
		next_settings();
		break;
	case ButtonNames::Scoreboard:
		next_scoreboard();
		break;
	case ButtonNames::ResetLevel:
		next_reset_level();
		break;
	case ButtonNames::Exit:
		next_exit();
		break;
	case ButtonNames::MainMenu:
		next_main_menu();
		break;
	}
}

/*
Bool that hold if we had a state change
*/
bool InGameMenu::satate_changed()
{
	return sate_changed;
}



//========================All loading functions:
/*
Loads all textures
*/
void InGameMenu::load_textures()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("continue.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("main_menu_png.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("reset_button.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("setting_button.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("exit_button.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("pause.png");
	m_textures.push_back(texture);
}

void InGameMenu::load_background()
{
	float scale_height = float(HEIGHT) / 900.f,
		scale_width = float(WIDTH) / 1200.f;

	background.setTexture(*m_textures[6]);
	background.scale(scale_width, scale_height);
}

void InGameMenu::load_buttons()
{
	Button Continue(m_textures[0], sf::Vector2f(300, 300), ButtonNames::Continue);
	m_buttons.push_back(Continue);
	
	Button main_menu(m_textures[1], sf::Vector2f(300, 400), ButtonNames::MainMenu);
	m_buttons.push_back(main_menu);

	Button reset_level(m_textures[2], sf::Vector2f(300, 500), ButtonNames::ResetLevel);
	m_buttons.push_back(reset_level);

	Button settings(m_textures[3], sf::Vector2f(300, 600), ButtonNames::Settings);
	m_buttons.push_back(settings);


	Button exit(m_textures[4], sf::Vector2f(300, 700), ButtonNames::Exit);
	m_buttons.push_back(exit);
}
void InGameMenu::load_arrow()
{
	m_arrow = Selection(m_textures[5], sf::Vector2f(250, 300));
}

