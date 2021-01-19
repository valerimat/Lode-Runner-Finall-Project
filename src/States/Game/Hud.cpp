#include "Hud.h"
#include "Player.h"
#include <iostream>

// c-tor
Hud::Hud()
{
}
//-----------------------------------------------------------------------------

// c-tor
Hud::Hud(Player* player, int num_of_level, int *time) :
	m_player(player), m_number_of_level(num_of_level+1), m_time(time)
{
	m_clock = &Clock::GetClock();
	m_score = &Score::GetScore();

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
void Hud::up_level()
{
	++m_number_of_level;
}
// draws the lives <3
void Hud::DrawLives(sf::RenderWindow& window)
{

	int i = lives;
	
	sf::Sprite score_sprt;
	score_sprt.setTexture(*m_textures[11]);
	score_sprt.setPosition(sf::Vector2f( 0,0));
	score_sprt.scale(sf::Vector2f(0.8,0.8));

	sf::Sprite three;
	three.setTexture(*m_textures[lives]);
	three.setPosition(sf::Vector2f(50, 0));
	three.scale(sf::Vector2f(0.8, 0.8));


	window.draw(score_sprt);
	window.draw(three);

	//int score = get_score();
}
//-----------------------------------------------------------------------------

// draws the time
void Hud::DrawTime(sf::RenderWindow& window)
{
	int i = m_textures.size();
	int time = *m_time - m_clock->GetPassedSeconds(), // 60 will be changed 
			   left_digit, right_digit;

	left_digit  = time / 10;
	right_digit = time % 10;

	sf::Sprite time_sprt;
	time_sprt.setTexture(*m_textures[12]);
	time_sprt.setPosition(sf::Vector2f(100, 0));
	time_sprt.scale(sf::Vector2f(0.8, 0.8));

	sf::Sprite left;
	left.setTexture(*m_textures[left_digit]);
	left.setPosition(sf::Vector2f(225, 0));
	left.scale(sf::Vector2f(0.8, 0.8));

	sf::Sprite right;
	right.setTexture(*m_textures[right_digit]);
	right.setPosition(sf::Vector2f(250, 0));
	right.scale(sf::Vector2f(0.8, 0.8));


	window.draw(time_sprt);
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
	score_sprt.setPosition(sf::Vector2f(575, 0));
	score_sprt.scale(sf::Vector2f(0.8, 0.8));

	sf::Sprite zero1;
	zero1.setTexture(*m_textures[0]);
	zero1.setPosition(sf::Vector2f(675, 0));
	zero1.scale(sf::Vector2f(0.8, 0.8));

	sf::Sprite zero2;
	zero2.setTexture(*m_textures[0]);
	zero2.setPosition(sf::Vector2f(700, 0));
	zero2.scale(sf::Vector2f(0.8, 0.8));


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
	int score = m_score->GetPoints();


	sf::Sprite score_sprt;
	score_sprt.setTexture(*m_textures[10]);
	score_sprt.setPosition(sf::Vector2f(300, 0));
	score_sprt.scale(sf::Vector2f(0.8, 0.8));

	sf::Sprite digit1;
	digit1.setTexture(*m_textures[score%10]);
	digit1.setPosition(sf::Vector2f(525, 0)); 
	digit1.scale(sf::Vector2f(0.8, 0.8));

	score /= 10;

	sf::Sprite digit2;
	digit2.setTexture(*m_textures[score % 10]);
	digit2.setPosition(sf::Vector2f(500, 0)); 
	digit2.scale(sf::Vector2f(0.8, 0.8));

	score /= 10;

	sf::Sprite digit3;
	digit3.setTexture(*m_textures[score % 10]);
	digit3.setPosition(sf::Vector2f(475, 0)); 
	digit3.scale(sf::Vector2f(0.8, 0.8));

	score /= 10;

	sf::Sprite digit4;
	digit4.setTexture(*m_textures[score % 10]);
	digit4.setPosition(sf::Vector2f(450, 0));
	digit4.scale(sf::Vector2f(0.8, 0.8));

	window.draw(score_sprt);
	window.draw(digit1);
	window.draw(digit2);
	window.draw(digit3);
	window.draw(digit4);

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
	lives = m_player->GetLives();
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