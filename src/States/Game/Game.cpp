#include "Game.h"
#include "MainMenu.h"
#include "InGameMenu.h"
#include "Clock.h"
#include "MacroSettings.h"

Game::Game():
	m_maps(MapData())
{
	Clock::GetClock().RestartTime();
	load();
	init_controllers();
}
//=============================================================================

//=============================================================================
void Game::load()
{
	MacroSettings::GetSettings().SetMapHeight(m_maps.GetCurrHeight(level));
	MacroSettings::GetSettings().SetMapWidth(m_maps.GetCurrWidth(level));

	Map temp(m_maps.GetMap(level), m_maps.GetCurrHeight(level), m_maps.GetCurrWidth(level), m_maps.GetCurrTimer(level));
	m_curr_map = temp;

	Hud hud(m_curr_map.get_player(), level, m_curr_map.GetTimer());
	m_hud = hud;
	
}
//=============================================================================

//=============================================================================
void Game::Draw(sf::RenderWindow &window)
{
	m_curr_map.Draw(window);
	m_hud.Draw(window);
}
//=============================================================================

//=============================================================================
Map * Game::get_curr_map()
{
	return & m_curr_map;
}
//=============================================================================

//=============================================================================
void Game::init_controllers()
{
	//can move it to one array
	m_enemy_cont = std::make_shared<EnemyController>(get_curr_map());
	m_enemy_cont->InitController();

	m_player_cont = std::make_shared<PlayerController>(get_curr_map());
	m_player_cont->InitController();
}
//=============================================================================

//=============================================================================
void Game::on_update()
{
	if (m_curr_map.all_coins_collected())
	{
		if (max_level())
		{
			set_next_state(States::Win);
			return;
		}
		advance_level();
		
	}


	if (m_curr_map.get_player()->GetLives() == 0)
		set_next_state(States::Death);

	m_enemy_cont->SetPaths();
	m_curr_map.check_holes();
	m_curr_map.close_holes();
}
//=============================================================================

//=============================================================================
void Game::handle_event(float dt)
{
	check_preseed_now();
	check_release();

	m_enemy_cont->MoveEnemies(dt);
	m_player_cont->MovePlayer(dt);

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
	(&Score::GetScore())->advance_level();
	m_hud.up_level();
	reset_level();
	MacroSettings::GetSettings().SetHeight(m_maps.GetCurrHeight(level));
	MacroSettings::GetSettings().SetWidth(m_maps.GetCurrWidth(level));
}
//=============================================================================

//=============================================================================
bool Game::max_level()
{
	if ((level + 1) >= m_maps.get_number_of_levels())
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
	Clock::GetClock().RestartTime();
}
//=============================================================================

//=============================================================================
void Game::reset_game()
{
	level = 0;
	load();
	init_controllers();
}
//=============================================================================