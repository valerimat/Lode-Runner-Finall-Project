#include "Game.h"
#include "MainMenu.h"
#include "InGameMenu.h"
#include "Clock.h"
#include "MacroSettings.h"

Game::Game():
	m_maps(MapData())
{
	Score::GetScore().reset_score();
	Clock::get_clock().restart_time();
	load();
	init_controllers();
}
//=============================================================================

//=============================================================================
void Game::load()
{
	MacroSettings::get_settings().set_map_height(m_maps.get_curr_height(level));
	MacroSettings::get_settings().set_map_width(m_maps.get_curr_width(level));

	m_curr_map = new Map(m_maps.get_map(level), m_maps.get_curr_height(level), m_maps.get_curr_width(level), m_maps.get_curr_time(level));

	Hud hud(m_curr_map->get_player()->get_lives(),level, m_curr_map->get_timer());
	m_hud = hud;
	
}
//=============================================================================

//=============================================================================
void Game::Draw(sf::RenderWindow &window)
{
	m_curr_map->Draw(window);
	m_hud.Draw(window);
}
//=============================================================================

//=============================================================================
Map * Game::get_curr_map()
{
	return  m_curr_map;
}
//=============================================================================

//=============================================================================
void Game::init_controllers()
{
	//can move it to one array
	m_controllers.clear();
	m_controllers.push_back(std::make_unique< EnemyController>(get_curr_map()));
	m_controllers.push_back(std::make_unique< PlayerController>(get_curr_map()));
	
	for (int i = 0; i < m_controllers.size(); ++i)
		m_controllers[i]->init_controller();
}
//=============================================================================

//=============================================================================
void Game::on_update()
{
	if (m_curr_map->all_coins_collected())
	{
		if (max_level())
		{
			set_next_state(States::Win);
			return;
		}
		advance_level();
		
	}

	if (timeIsUp())
	{
		Music::get_music().busted_sound();
		set_next_state(States::Death);
		return;
	}


	if (m_curr_map->get_player()->get_lives() == 0)
	{
		Music::get_music().busted_sound();
		set_next_state(States::Death);
		return;
	}

	m_hud.set_lives(m_curr_map->get_player()->get_lives());
	m_curr_map->check_holes();
	m_curr_map->close_holes();
}
//=============================================================================

//=============================================================================
void Game::handle_event(float dt)
{
	check_preseed_now();
	check_release();

	for (int i = 0; i < m_controllers.size(); ++i)
		m_controllers[i]->move(dt);
}
//=============================================================================

//=============================================================================
void Game::check_release()
{
	if (was_pressed == sf::Keyboard::Escape && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
	{
		set_next_state(States::InGameMenu);
		was_pressed = sf::Keyboard::Unknown;
	}
}
//=============================================================================

//=============================================================================
void Game::check_preseed_now()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		was_pressed = sf::Keyboard::Escape;
	}
}
//=============================================================================

//level related stuff:

//=============================================================================
void Game::advance_level()
{
	++level;

	MacroSettings::get_settings().set_map_height(m_maps.get_curr_height(level));
	MacroSettings::get_settings().set_map_width(m_maps.get_curr_width(level));
	Score::GetScore().advance_level();
	m_hud.up_level();
	reset_level();

}
//=============================================================================

//=============================================================================
bool Game::max_level()
{
	if ((level + 1) >= m_maps.get_num_of_levels())
	{
		return true;
	}
	return false;
}
//=============================================================================

//=============================================================================
void Game::reset_level()
{
	//(need to reset time
	load();
	init_controllers();
	Clock::get_clock().restart_time();
}
//=============================================================================

//=============================================================================
void Game::reset_game()
{
	Score::GetScore().reset_score();
	level = 0;
	load();
	init_controllers();
}
//=============================================================================

//=============================================================================
bool Game::timeIsUp()
{
	int time = m_maps.get_curr_time(level);
	if (time - Clock::get_clock().get_passed_seconds() < 0)
		return true;

	return false;
}
//=============================================================================