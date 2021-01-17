#include "Death.h"
#include "Game.h"	
#include "Settings.h"
#include "MainMenu.h"

Death::Death()
{
	my_state = (StateEnum::Main);
	next_state = (StateEnum::Main);
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
	set_prev_state(nullptr);
}
//-----------------------------------------------------------------------------

void Death::set_prev_state(State* state)
{
	m_previouse_screen = state;
}


void Death::Load()
{
	
}
//-----------------------------------------------------------------------------


State* Death::get_next_state()
{
	sate_changed = false;
	return next_screen;
}

void Death::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].Draw(window);

	m_arrow.Draw(window);

	window.draw(wasted);
}
//-----------------------------------------------------------------------------

void Death::on_update()
{
	
}


void Death::handle_event(float dt)
{

	check_preseed_now();
	check_release();

}

void  Death::set_next_state(ButtonNames next_state)
{
	State* next;
	switch (next_state)
	{
	case ButtonNames::Play:
		next = new Game;
		sate_changed = true;
		next_screen = next;
		break;
	case ButtonNames::MainMenu:
		next = new MainMenu;
		sate_changed = true;
		next_screen = next;
		break;
	case ButtonNames::Exit:
		exit(EXIT_SUCCESS);
		break;
	}
}

bool Death::satate_changed()
{
	return sate_changed;
}


void Death::load_background()
{
	wasted.setTexture(*m_textures[0]);
	wasted.setPosition(300, 100);
	wasted.setScale(sf::Vector2f(0.5, 0.5));
}

void Death::load_buttons()
{
	Button play(m_textures[1], sf::Vector2f(300, 300), ButtonNames::Play);
	m_buttons.push_back(play);

	Button main(m_textures[2], sf::Vector2f(300, 400), ButtonNames::MainMenu);
	m_buttons.push_back(main);

	Button settings(m_textures[2], sf::Vector2f(300, 500), ButtonNames::Exit);
	m_buttons.push_back(settings);
}

void Death::load_arrow()
{
	m_arrow = Selection(m_textures[3], sf::Vector2f(250, 300));
}

void Death::load_textures()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("wasted.png");
	m_textures.push_back(texture);

	//MAIN MENU BUTTON
	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("play_button.png");
	m_textures.push_back(texture);

	
	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("setting_button.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);
	
}
