#include "PlayerController.h"
#include "Player.h"
#include "Map.h"


void PlayerController::init_controller()
{
	m_player = m_map->GetPlayer();
	m_player->set_map(m_map);
}
//-----------------------------------------------------------------------------

void PlayerController::MovePlayer( float dt)
{
	sf::Keyboard::Key key;

	check_key_press(key);

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

	m_map->IsOnLadder(m_player->get_location());
}
//-----------------------------------------------------------------------------

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
	else
		pressed = sf::Keyboard::End;
}