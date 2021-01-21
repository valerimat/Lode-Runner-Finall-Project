#include "Hud.h"
#include "Player.h"
#include <iostream>

// c-tor
//=============================================================================
Hud::Hud()
{
	
}
//=============================================================================

// c-tor
//=============================================================================
Hud::Hud(int lives,int num_of_level, int *time) :
	m_lives(lives), m_number_of_level(num_of_level+1), m_time(time)
{
	m_clock = &Clock::get_clock();
	m_score = &Score::GetScore();
	
	load_textures();
	load();
}
//=============================================================================

// draws the given HUD
//=============================================================================
void Hud::Draw(sf::RenderWindow& window)
{
	set_score();

	draw_score(window);
	draw_lives(window);
	draw_level(window);
	draw_time(window);
}
//=============================================================================

//=============================================================================
void Hud::up_level()
{
	++m_number_of_level;
}
//=============================================================================

// draws the lives <3
//=============================================================================
void Hud::draw_lives(sf::RenderWindow& window)
{

	int i = m_lives;
	if (m_lives < 0)
		return;

	lives_digits[0]->setTexture(*m_textures[m_lives % 10]);

	window.draw(*m_stable[3]);
	window.draw(*lives_digits[0]);

}
//=============================================================================

//=============================================================================
void Hud::draw_time(sf::RenderWindow& window)
{
	int i = m_textures.size();
	int time = *m_time - m_clock->get_passed_seconds(), // 60 will be changed 
			   left_digit, right_digit;

	left_digit  = time / 10;
	right_digit = time % 10;
	if (left_digit < 0 || right_digit < 0)
		return;


	time_digits[0]->setTexture(*m_textures[left_digit]);
	time_digits[1]->setTexture(*m_textures[right_digit]);

	sf::Sprite right;

	window.draw(*m_stable[0]);
	window.draw(*time_digits[0]);
	window.draw(*time_digits[1]);


}
//=============================================================================

// draws the current lvl we are playing
//=============================================================================
void Hud::draw_level(sf::RenderWindow& window)
{
	int i = m_textures.size();
	int level = m_number_of_level;
	


	level_digits[1]->setTexture(*m_textures[level % 10]);

	level /= 10;

	level_digits[0]->setTexture(*m_textures[level % 10]);


	window.draw(*m_stable[2]);
	window.draw(*level_digits[1]);
	window.draw(*level_digits[0]);
}
//=============================================================================

// draws the player's score
//=============================================================================
void Hud::draw_score(sf::RenderWindow& window)
{
	int i = m_textures.size();
	int score = m_score->get_points();


	score_digits[0]->setTexture(*m_textures[score % 10]);

	score /= 10;
	
	score_digits[1]->setTexture(*m_textures[score % 10]);

	score /= 10;

	score_digits[2]->setTexture(*m_textures[score % 10]);

	score /= 10;

	score_digits[3]->setTexture(*m_textures[score % 10]);
	

	window.draw(*m_stable[1]);
	window.draw(*score_digits[0]);
	window.draw(*score_digits[1]);
	window.draw(*score_digits[2]);
	window.draw(*score_digits[3]);
}
//=============================================================================

// sets the score
//=============================================================================
void Hud::set_score()
{
	//int score = score->get_score();
}
//=============================================================================

// sets the lives
//=============================================================================
void Hud::set_lives(int lives) 
{
	m_lives = lives;
}
//=============================================================================


// loads all the needed the textures for the sprite
//=============================================================================
void Hud::load_textures()
{
	int i = 0;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number0.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number1.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number2.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number3.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number4.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number5.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number6.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number7.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number8.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("number9.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("score.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("hert.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("time.png");
	++i;
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[i]->loadFromFile("lvl.png");

}
//=============================================================================

//=============================================================================
void Hud::load()
{
	load_stable();
	load_level_digits();
	load_score_digits();
	load_time_digits();
	load_lives_digits();
}
//=============================================================================

//=============================================================================
void Hud::load_stable()
{
	sf::Sprite time_sprt;
	time_sprt.setTexture(*m_textures[12]);
	time_sprt.setPosition(sf::Vector2f(100, 0));
	time_sprt.scale(sf::Vector2f(0.8, 0.8));

	m_stable.push_back(std::make_unique <sf::Sprite>(time_sprt));

	sf::Sprite score_sprt;
	score_sprt.setTexture(*m_textures[10]);
	score_sprt.setPosition(sf::Vector2f(300, 0));
	score_sprt.scale(sf::Vector2f(0.8, 0.8));

	m_stable.push_back(std::make_unique <sf::Sprite>(score_sprt));


	sf::Sprite level_sprt;
	level_sprt.setTexture(*m_textures[13]);
	level_sprt.setPosition(sf::Vector2f(575, 0));
	level_sprt.scale(sf::Vector2f(0.8, 0.8));

	m_stable.push_back(std::make_unique <sf::Sprite>(level_sprt));

	sf::Sprite lives_sprt;
	lives_sprt.setTexture(*m_textures[11]);
	lives_sprt.setPosition(sf::Vector2f(0, 0));
	lives_sprt.scale(sf::Vector2f(0.8, 0.8));

	m_stable.push_back(std::make_unique <sf::Sprite>(lives_sprt));
}

//=============================================================================
void Hud::load_level_digits()
{
	sf::Sprite first_digit;
	first_digit.setPosition(sf::Vector2f(675, 0));
	first_digit.scale(sf::Vector2f(0.8, 0.8));

	level_digits.push_back(std::make_unique<sf::Sprite>(first_digit));

	sf::Sprite second_digit;
	second_digit.setPosition(sf::Vector2f(700, 0));
	second_digit.scale(sf::Vector2f(0.8, 0.8));

	level_digits.push_back(std::make_unique<sf::Sprite>(second_digit));
}
//=============================================================================

//=============================================================================
void Hud::load_score_digits()
{
	sf::Sprite digit1;

	digit1.setPosition(sf::Vector2f(525, 0));
	digit1.scale(sf::Vector2f(0.8, 0.8));
	score_digits.push_back(std::make_unique<sf::Sprite>(digit1));


	sf::Sprite digit2;
	digit2.setPosition(sf::Vector2f(500, 0));
	digit2.scale(sf::Vector2f(0.8, 0.8));
	score_digits.push_back(std::make_unique<sf::Sprite>(digit2));

	sf::Sprite digit3;
	digit3.setPosition(sf::Vector2f(475, 0));
	digit3.scale(sf::Vector2f(0.8, 0.8));
	score_digits.push_back(std::make_unique<sf::Sprite>(digit3));

	sf::Sprite digit4;
	digit4.setPosition(sf::Vector2f(450, 0));
	digit4.scale(sf::Vector2f(0.8, 0.8));
	score_digits.push_back(std::make_unique<sf::Sprite>(digit4));
}
//=============================================================================

//=============================================================================
void Hud::load_time_digits()
{
	sf::Sprite digit1;
	digit1.setPosition(sf::Vector2f(225, 0));
	digit1.scale(sf::Vector2f(0.8, 0.8));
	time_digits.push_back(std::make_unique<sf::Sprite>(digit1));


	sf::Sprite digit2;
	digit2.setPosition(sf::Vector2f(250, 0));
	digit2.scale(sf::Vector2f(0.8, 0.8));
	time_digits.push_back(std::make_unique<sf::Sprite>(digit2));

}
//=============================================================================

//=============================================================================
void Hud::load_lives_digits()
{
	sf::Sprite lives_digit;
	lives_digit.setPosition(sf::Vector2f(50, 0));
	lives_digit.scale(sf::Vector2f(0.8, 0.8));

	lives_digits.push_back(std::make_unique<sf::Sprite>(lives_digit));
}
//=============================================================================