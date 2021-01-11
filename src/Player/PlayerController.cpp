#include "PlayerController.h"
#include "Player.h"
#include "Map.h"

/*
PlayerController::PlayerController(Map& map)
{
	m_player = map.get_player();
}
*/

void PlayerController::init_controller()
{
	m_player = m_map->GetPlayer();
}
//-----------------------------------------------------------------------------

void PlayerController::MovePlayer(sf::Keyboard::Key key, float dt)
{
	NextStep next_wanted = NextStep::NONE;

	int x = m_player->get_location().x;

	switch (key)
	{
    case sf::Keyboard::Left:
		next_wanted = NextStep::LEFT;
		if(x % 40 == 0)
			m_music->RunningSound();
        break;
    case sf::Keyboard::Right:
		next_wanted = NextStep::RIGHT;
		if (x % 40 == 0)
			m_music->RunningSound();
        break;
    case sf::Keyboard::Up:
		next_wanted = NextStep::UP;
        break;
    case sf::Keyboard::Down:
		next_wanted = NextStep::DOWN;
        break;
	case sf::Keyboard::End:
		next_wanted = NextStep::DOWN;
		break;
	}
	
	std::vector <NextStep> avaliable_steps = m_player->GetValid();
	
	if (avaliable_steps.size() == 1) 
	{
		if (avaliable_steps[0] == NextStep::DOWN)
		{
			sf::Keyboard::Key key = sf::Keyboard::Down;
			m_player->Move(key, dt);
			return;
		}
	}
		
	for (int i = 0; i < avaliable_steps.size(); ++i)
	{
		if (avaliable_steps[i] == next_wanted)
			m_player->Move(key,dt);
	}

	if (m_map->IsOnCoin(m_player->get_location()) != -1)
	{
		m_map->DeleteCoin(m_map->IsOnCoin(m_player->get_location()));
	}
}
//-----------------------------------------------------------------------------

void PlayerController::set_paths()
{
	m_player->SetValid(get_avaliable_steps(m_player->get_location()));
}
//-----------------------------------------------------------------------------