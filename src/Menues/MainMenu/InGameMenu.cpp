#include "InGameMenu.h"
#include "Game.h"	
#include "Settings.h"

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

	//check _which button pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		set_next_state(m_buttons[index_of_selected_button].get_name());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		if (m_previouse_screen != nullptr)
			set_next_state(ButtonNames::Back);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		index_of_selected_button = (index_of_selected_button + 1) % m_buttons.size();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		index_of_selected_button = (index_of_selected_button + 1) % m_buttons.size();
		m_arrow.move_arrow(m_buttons[index_of_selected_button].get_location());
	}

}
//========================States and teyr handeling:



void  InGameMenu::set_next_state(ButtonNames next_state)
{
	State* next;
	switch (next_state)
	{
	case ButtonNames::Back:
		if (m_previouse_screen != nullptr)
			sate_changed = true;
		next_screen = m_previouse_screen;
		break;
	case ButtonNames::Continue:
		if (m_previouse_screen != nullptr)
			sate_changed = true;
		next_screen = m_previouse_screen;
		break;
	case ButtonNames::Settings:
		next = new Settings;
		sate_changed = true;
		next_screen = next;
		break;
	case ButtonNames::Scoreboard:
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
	texture->loadFromFile("play_button.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("setting_button.png");
	m_textures.push_back(texture);
}

void InGameMenu::load_background()
{

}

void InGameMenu::load_buttons()
{
	Button Continue(m_textures[0], sf::Vector2f(300, 300), ButtonNames::Continue);
	m_buttons.push_back(Continue);
	

	Button settings(m_textures[2], sf::Vector2f(300, 400), ButtonNames::Settings);
	m_buttons.push_back(settings);
}
void InGameMenu::load_arrow()
{
	m_arrow = Selection(m_textures[1], sf::Vector2f(250, 300));
}