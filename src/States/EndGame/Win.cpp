#include "Win.h"
#include "Game.h"	
#include "Settings.h"
#include "MainMenu.h"
#include "Score.h"
#include <string>


//C-tor:
//=============================================================================
Win::Win(int score)
{
	m_score = score;
	load();
}
//=============================================================================

//D-tor:
//=============================================================================
Win::~Win()
{
	for (int i = 0; i < m_textures.size(); ++i)
	{
		delete (m_textures[i]);
	}
	delete font;
}
//=============================================================================

//=============================================================================
void Win::load()
{
	load_text(m_score);
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
}
//=============================================================================

//Draw:
//=============================================================================
void Win::Draw(sf::RenderWindow& window)
{
	window.draw(background);

	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].Draw(window);

	m_arrow.Draw(window);

	window.draw(text);

}
//=============================================================================

//=============================================================================
void Win::on_update()
{
	//get_name();
}
//=============================================================================

//=============================================================================
void Win::handle_event(float dt)
{
	check_preseed_now();
	check_release();	
}
//=============================================================================

//Load:
//=============================================================================
void Win::load_text(int score)
{
	font = new sf::Font;
	font->loadFromFile("8-bit-hud.ttf");
	std::string str = std::to_string(m_score);
	text.setCharacterSize(40);
	text.setFont(*font);
	text.setString(str);
	text.setColor(sf::Color(255, 211, 7));
	text.setOutlineColor(sf::Color(76, 10, 95));
	text.setOutlineThickness(4);
	text.setPosition(sf::Vector2f(450, 300));
}
//=============================================================================

//=============================================================================
void Win::load_background()
{
	float scale_height = float(HEIGHT) / 900.f,
		scale_width = float(WIDTH) / 1200.f;

	background.setTexture(*m_textures[4]);
	background.scale(scale_width, scale_height);
}
//=============================================================================

//=============================================================================
void Win::load_buttons()
{
	Button play(m_textures[0], sf::Vector2f(300, 550), States::Play);
	m_buttons.push_back(play);

	Button main(m_textures[1], sf::Vector2f(300, 650), States::MainMenu);
	m_buttons.push_back(main);

	Button settings(m_textures[2], sf::Vector2f(300, 750), States::Exit);
	m_buttons.push_back(settings);
}
//=============================================================================

//=============================================================================
void Win::load_arrow()
{
	m_arrow = Selection(m_textures[3], sf::Vector2f(250, 550));
}
//=============================================================================

//=============================================================================
void Win::load_textures()
{
	auto texture = new sf::Texture;
	texture->loadFromFile("play_again_button.png");
	m_textures.push_back(texture);

	//MAIN MENU BUTTON
	texture = new sf::Texture;
	texture->loadFromFile("main_menu_png.png");
	m_textures.push_back(texture);


	texture = new sf::Texture;
	texture->loadFromFile("exit_button.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);

	texture = new sf::Texture;
	texture->loadFromFile("victory.png");
	m_textures.push_back(texture);

}
//=============================================================================