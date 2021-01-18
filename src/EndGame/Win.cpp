#include "Win.h"
#include "Game.h"	
#include "Settings.h"
#include "MainMenu.h"
#include "Score.h"
#include <string>

Win::Win(int score)
{
	my_state = (StateEnum::Main);
	next_state = (StateEnum::Main);
	m_score = score;
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
	set_prev_state(nullptr);
}
//-----------------------------------------------------------------------------

void Win::set_prev_state(State* state)
{
	m_previouse_screen = state;
}


void Win::Load()
{

}
//-----------------------------------------------------------------------------


State* Win::get_next_state()
{
	sate_changed = false;
	return next_screen;
}

void Win::Draw(sf::RenderWindow& window)
{
	window.draw(background);

	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].Draw(window);

	m_arrow.Draw(window);
	sf::Font font;
	font.loadFromFile("8-bit-hud.ttf");
	std::string str = std::to_string(m_score);
	text.setCharacterSize(40);
	text.setFont(font);
	text.setString(str);
	text.setColor(sf::Color(255, 211, 7));
	text.setOutlineColor(sf::Color(76, 10, 95));
	text.setOutlineThickness(4);
	text.setPosition(sf::Vector2f(450, 300));

	window.draw(text);

	
}
//-----------------------------------------------------------------------------

void Win::on_update()
{
	//get_name();
}


void Win::handle_event(float dt)
{
	
	check_preseed_now();
	check_release();
	
}

void  Win::set_next_state(ButtonNames next_state)
{
	State* next;
	switch (next_state)
	{
	case ButtonNames::Play:
		next_game();
		break;
	case ButtonNames::MainMenu:
		next_main_menu();
		break;
	case ButtonNames::Exit:
		next_exit();
		break;
	}
}

bool Win::satate_changed()
{
	return sate_changed;
}


void Win::load_background()
{
	float scale_height = float(HEIGHT) / 900.f,
		scale_width = float(WIDTH) / 1200.f;

	background.setTexture(*m_textures[4]);
	background.scale(scale_width, scale_height);
}

void Win::load_buttons()
{
	Button play(m_textures[0], sf::Vector2f(300, 550), ButtonNames::Play);
	m_buttons.push_back(play);

	Button main(m_textures[1], sf::Vector2f(300, 650), ButtonNames::MainMenu);
	m_buttons.push_back(main);

	Button settings(m_textures[2], sf::Vector2f(300, 750), ButtonNames::Exit);
	m_buttons.push_back(settings);
}

void Win::load_arrow()
{
	m_arrow = Selection(m_textures[3], sf::Vector2f(250, 550));
}

void Win::load_textures()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("play_again_button.png");
	m_textures.push_back(texture);

	//MAIN MENU BUTTON
	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("main_menu_png.png");
	m_textures.push_back(texture);


	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("exit_button.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("victory.png");
	m_textures.push_back(texture);

}


void Win::check_release()
{
	if (was_pressed == sf::Keyboard::Enter && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
	{
		set_next_state(m_buttons[index_of_selected_button].get_name());
		was_pressed = sf::Keyboard::Unknown;
	}
	if (was_pressed == sf::Keyboard::Up && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
	{
		index_of_selected_button = (index_of_selected_button - 1) % m_buttons.size();
		m_arrow.move_arrow(m_buttons[index_of_selected_button].get_location());
		was_pressed = sf::Keyboard::Unknown;
	}
	if (was_pressed == sf::Keyboard::Down && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		index_of_selected_button = (index_of_selected_button + 1) % m_buttons.size();
		m_arrow.move_arrow(m_buttons[index_of_selected_button].get_location());
		was_pressed = sf::Keyboard::Unknown;
	}
}


void Win::check_preseed_now()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		was_pressed = sf::Keyboard::Enter;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		was_pressed = sf::Keyboard::Escape;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		was_pressed = sf::Keyboard::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		was_pressed = sf::Keyboard::Up;
	}
}


