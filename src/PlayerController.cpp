#include "PlayerController.h"
#include "Player.h"
#include "Map.h"

PlayerController::PlayerController(Map& map)
{
	m_player = map.get_player();
}


void PlayerController::move_player(sf::Keyboard::Key key)
{
	// later we add if statments
	m_player->move(key);
}