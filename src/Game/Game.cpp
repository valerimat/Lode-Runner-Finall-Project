#include "Game.h"
#include "MainMenu.h"
#include "InGameMenu.h"
#include "Clock.h"

Game::Game():
	m_maps(MapData())
{
	Load();
	init_controllers();
	set_prev_state(nullptr);
}
//-----------------------------------------------------------------------------

void Game::set_prev_state(State* state)
{
	m_previouse_screen = state;
}

void Game::Load()
{
	Map temp(m_maps.GetMap(level), m_maps.GetCurrHeight(level), m_maps.GetCurrWidth(level), m_maps.GetCurrTimer(level));
	m_curr_map = temp;

	Hud hud(m_curr_map.get_player(), level, m_curr_map.GetTimer());
	m_hud = hud;
}
//-----------------------------------------------------------------------------
void Game::reset_level()
{
	//(need to reset time
	Load();
	init_controllers();
	Clock::GetClock().RestartTime();
}

void Game::reset_game()
{
	level = 0;
	Load();
	init_controllers();
}

State* Game::get_next_state()
{
	sate_changed = false;
	return next_screen;
}

void Game::Draw(sf::RenderWindow &window)
{
	m_curr_map.Draw(window);
	m_hud.Draw(window);
}
//-----------------------------------------------------------------------------

Map * Game::get_curr_map()
{
	return & m_curr_map;
}
//-----------------------------------------------------------------------------

void Game::init_controllers()
{
	//can move it to one array
	m_enemy_cont = std::make_shared<EnemyController>(get_curr_map());
	m_enemy_cont->init_controller();

	m_player_cont = std::make_shared<PlayerController>(get_curr_map());
	m_player_cont->init_controller();
}

void Game::on_update()
{
	if (m_curr_map.all_coins_collected())
	{
		if (max_level())
		{
			set_next_state(ButtonNames::Win);
			return;
		}
		advance_level();
	}


	if (m_curr_map.get_player()->get_lives() == 0)
		set_next_state(ButtonNames::Death);

	m_enemy_cont->set_paths();
	m_curr_map.check_holes();
	m_curr_map.close_holes();
}


void Game::handle_event(float dt)
{
	check_preseed_now();
	check_release();

	m_enemy_cont->move_enemies(dt);
	m_player_cont->MovePlayer(dt);

}

void  Game::set_next_state(ButtonNames next_state)
{
	State * next;
	switch (next_state)
	{
	case ButtonNames::InGameMenu:
		next_in_game_menu();
		break;
	case ButtonNames::Death:
		next_death_screen();
		break;
	case ButtonNames::Win:
		next_win(m_score.GetPoints());
		m_score.reset_score();
		break;
	}
}

bool Game::satate_changed()
{
	return sate_changed;
}

void Game::check_release()
{
	if (was_pressed == sf::Keyboard::Escape && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
	{
		set_next_state(ButtonNames::InGameMenu);
		was_pressed = sf::Keyboard::Unknown;
	}
}

void Game::check_preseed_now()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		was_pressed = sf::Keyboard::Escape;
	}
}

void Game::advance_level()
{
	++level;
	reset_level();
}

bool Game::max_level()
{
	if ((level + 1) >= m_maps.get_number_of_levels())
	{
		return true;
	}
	return false;
}