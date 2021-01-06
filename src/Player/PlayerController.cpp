#include "PlayerController.h"
#include "Player.h"
#include "Map.h"

/*
PlayerController::PlayerController(Map& map)
{
	m_player = map.get_player();
}
*/

void PlayerController::init_player()
{
	m_player = m_map->get_player();
}


void PlayerController::move_player(sf::Keyboard::Key key, float dt)
{
	/*
	std::vector<char> collision = m_player->is_on_something(map, key);

	for (int i = 0; i < collision.size(); i++)
	{
		std::cout << collision[i] << " ";
	}
	

	physics_player(key, map, collision);
	*/
	NextStep next_wanted = NextStep::NONE;

	switch (key)
	{
    case sf::Keyboard::Left:
		next_wanted = NextStep::LEFT;
        break;
    case sf::Keyboard::Right:
		next_wanted = NextStep::RIGHT;
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
	
	std::vector <NextStep> avaliable_steps = m_player->get_valid();
	
	if (avaliable_steps.size() == 1) 
	{
		if (avaliable_steps[0] == NextStep::DOWN)
		{
			sf::Keyboard::Key key = sf::Keyboard::Down;
			m_player->move(key, dt);
			return;
		}
	}
		

	for (int i = 0; i < avaliable_steps.size(); ++i)
	{
		if (avaliable_steps[i] == next_wanted)
			m_player->move(key,dt);
	}
	
	//m_player->move(key);

	//if (m_player->is_on_ground(map))
		//std::cout << "GROUND\n";
	//if (m_player->is_on_ladder(map))
		//std::cout << "LADDER\n";
	//if (m_player->is_on_pole(map))
	//	std::cout << "POLE\n";
	//if (m_player->is_on_wall(map))
	//	std::cout << "WALL\n";
	//if (m_player->is_on_air(map))
	//	std::cout << "AIR\n";
	//if (m_player->is_on_coin(map))
	//	std::cout << "COIN\n";
}

/*
void PlayerController::physics_player(sf::Keyboard::Key key, Map& map, std::vector<char>& collision)
{
	bool ground = false, wall = false, ladder = false,
		 pole = false, coin = false, enemy = false;

	// lets us work will boolean values and be on track more easily
	for (int i = 0; i < collision.size(); i++)
	{
		if (collision[i] == GROUND)
			ground = true;
		if (collision[i] == WALL)
			wall = true;
		if (collision[i] == LADDER)
			ladder = true;
		if (collision[i] == POLE)
			pole = true;
		if (collision[i] == COIN)
			coin = true;
		if (collision[i] == ENEMY)
			enemy = true;
	}

	// free fall
	if (!ground && !ladder && !pole && key != sf::Keyboard::Up)
	{
		m_player->move(sf::Keyboard::Down);
		std::vector<char> collision = m_player->is_on_something(map, sf::Keyboard::Down);
		//std::this_thread::sleep_for(std::chrono::milliseconds(30));
		physics_player(key, map, collision);
	}

	// on ground
	if(ground && !wall && (key == sf::Keyboard::Left || key == sf::Keyboard::Right))
		m_player->move(key);

	// on ladder
	if (ladder && !wall)
	{
		if (ground && sf::Keyboard::Down)
			return;
		m_player->move(key);
		std::cout << "ladder\n";
	}

	// on pole
	if (pole && !wall && (key == sf::Keyboard::Left || key == sf::Keyboard::Right ||
		key == sf::Keyboard::Down))
		m_player->move(key);

	// wall = no movement forward
	if (wall)
	{
		std::cout << "wall\n";
		return;
	}
}
*/

void PlayerController::set_paths()
{
	m_player->set_valid(get_avaliable_steps(m_player->get_location()));
}