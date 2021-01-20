#include "PlayerController.h"
#include "Map.h"


void PlayerController::InitController()
{
	m_player = (m_map->get_player());
	m_player->SetMap(m_map);
}
//-----------------------------------------------------------------------------


void PlayerController::MovePlayer( float dt)
{
	sf::Keyboard::Key key;

	check_key_press(key);
	if (key != sf::Keyboard::X && key != sf::Keyboard::Z)
	{
		//if we are falling we cant move 
		if (!m_falling)
		{
			m_player->Move(key, dt);
		}

		//reset gravity bool
		m_player->turn_gravity_on();

		m_map->check_collision(*m_player);
		
		sf::Vector2f before_g = m_player->get_location();


		//do graviry do its job
		m_player->gravity(dt);

		//check collisions again
		m_map->check_collision(*m_player);

		sf::Vector2f after_g = m_player->get_location();

		//we are falling if we were able to go down
		if (before_g != after_g)
			m_falling = true;
		else
			m_falling = false;
	}
	else
	{
		if (key == sf::Keyboard::Z)
			m_player->DeleteLeft();
		else
			m_player->DeleteRight();
	}
}
//-----------------------------------------------------------------------------

void PlayerController::check_key_press(sf::Keyboard::Key& pressed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		pressed = sf::Keyboard::Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		pressed = sf::Keyboard::Right;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		pressed = sf::Keyboard::Up;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		pressed = sf::Keyboard::Down;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		pressed = sf::Keyboard::Z;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		pressed = sf::Keyboard::X;
}

