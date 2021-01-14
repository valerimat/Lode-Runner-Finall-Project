#include "Hud.h"
#include "Score.h"
#include "Player.h"
#include <iostream>
// c-tor
Hud::Hud()
{
}
//-----------------------------------------------------------------------------

// c-tor
Hud::Hud(Score* score, Player* player, int num_of_level) :
	m_score(score), m_player(player), m_number_of_level(num_of_level)
{
	m_clock = &Clock::GetClock();
	LoadTextures();
}
//-----------------------------------------------------------------------------

// draws the given HUD
void Hud::Draw(sf::RenderWindow& window)
{
	SetScore();
	SetLives();

	DrawScore(window);
	DrawLives(window);
	DrawLevel(window);
	DrawTime(window);
}
//-----------------------------------------------------------------------------

// draws the lives <3
void Hud::DrawLives(sf::RenderWindow& window)
{
	int i = m_textures.size();
	sf::Sprite score_sprt;
	score_sprt.setTexture(*m_textures[11]);
	score_sprt.setPosition(sf::Vector2f( 0,12.5));
	score_sprt.scale(sf::Vector2f(1, 1));

	sf::Sprite three;
	three.setTexture(*m_textures[3]);
	three.setPosition(sf::Vector2f(50, 12.5));
	three.scale(sf::Vector2f(1, 1));


	window.draw(score_sprt);
	window.draw(three);

	//int score = get_score();
}
//-----------------------------------------------------------------------------

// draws the time
void Hud::DrawTime(sf::RenderWindow& window)
{
	int i = m_textures.size();
	int time = 60 - m_clock->GetPassedTime(), // 60 will be changed 
			   left_digit, right_digit;

	left_digit  = time / 10;
	right_digit = time % 10;

	std::cout << time << std::endl;

	sf::Sprite score_sprt;
	score_sprt.setTexture(*m_textures[12]);
	score_sprt.setPosition(sf::Vector2f(100, 12.5));
	score_sprt.scale(sf::Vector2f(1, 1));

	sf::Sprite left;
	left.setTexture(*m_textures[left_digit]);
	left.setPosition(sf::Vector2f(225, 12.5));
	left.scale(sf::Vector2f(1, 1));

	sf::Sprite right;
	right.setTexture(*m_textures[right_digit]);
	right.setPosition(sf::Vector2f(250, 12.5));
	right.scale(sf::Vector2f(1, 1));


	window.draw(score_sprt);
	window.draw(left);
	window.draw(right);
	//int score = get_score();

}
//-----------------------------------------------------------------------------

// draws the current lvl we are playing
void Hud::DrawLevel(sf::RenderWindow& window)
{
	int i = m_textures.size();
	sf::Sprite score_sprt;
	score_sprt.setTexture(*m_textures[13]);
	score_sprt.setPosition(sf::Vector2f(575, 12.5));
	score_sprt.scale(sf::Vector2f(1, 1));

	sf::Sprite zero1;
	zero1.setTexture(*m_textures[0]);
	zero1.setPosition(sf::Vector2f(675, 12.5));
	zero1.scale(sf::Vector2f(1, 1));

	sf::Sprite zero2;
	zero2.setTexture(*m_textures[0]);
	zero2.setPosition(sf::Vector2f(700, 12.5));
	zero2.scale(sf::Vector2f(1, 1));


	window.draw(score_sprt);
	window.draw(zero1);
	window.draw(zero2);
	//int score = get_score();

}
//-----------------------------------------------------------------------------

// draws the player's score
void Hud::DrawScore(sf::RenderWindow& window)
{
	int i = m_textures.size();
	sf::Sprite score_sprt;
	score_sprt.setTexture(*m_textures[10]);
	score_sprt.setPosition(sf::Vector2f(300, 12.5));
	score_sprt.scale(sf::Vector2f(1, 1));

	sf::Sprite zero1;
	zero1.setTexture(*m_textures[0]);
	zero1.setPosition(sf::Vector2f(450, 12.5));
	zero1.scale(sf::Vector2f(1, 1));

	sf::Sprite zero2;
	zero2.setTexture(*m_textures[0]);
	zero2.setPosition(sf::Vector2f(475, 12.5));
	zero2.scale(sf::Vector2f(1, 1));

	sf::Sprite zero3;
	zero3.setTexture(*m_textures[0]);
	zero3.setPosition(sf::Vector2f(500, 12.5));
	zero3.scale(sf::Vector2f(1, 1));

	sf::Sprite zero4;
	zero4.setTexture(*m_textures[0]);
	zero4.setPosition(sf::Vector2f(525, 12.5));
	zero4.scale(sf::Vector2f(1, 1));

	window.draw(score_sprt);
	window.draw(zero1);
	window.draw(zero2);
	window.draw(zero3);
	window.draw(zero4);

	//int score = get_score();

}
//-----------------------------------------------------------------------------

// sets the score
void Hud::SetScore()
{
	//int score = score->get_score();
}
//-----------------------------------------------------------------------------

// sets the lives
void Hud::SetLives() 
{
	//int lives = m_player->get_lives();
}
//-----------------------------------------------------------------------------

// loads all the needed the textures for the sprite
void Hud::LoadTextures()
{
	auto texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number0.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number1.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number2.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number3.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number4.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number5.png");
	m_textures.push_back(texture_ptr);
	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number6.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number7.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number8.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("number9.png");
	m_textures.push_back(texture_ptr);

	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("score.png");
	m_textures.push_back(texture_ptr);
	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("hert.png");
	m_textures.push_back(texture_ptr);
	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("time.png");
	m_textures.push_back(texture_ptr);
	texture_ptr = std::make_shared<sf::Texture>();
	texture_ptr->loadFromFile("lvl.png");
	m_textures.push_back(texture_ptr);
}
//-----------------------------------------------------------------------------