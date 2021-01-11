#include "Game.h"

Game::Game():
	m_maps(MapData())
{
	Load();
	init_controllers();
}
//-----------------------------------------------------------------------------

void Game::Load()
{
	Map temp(m_maps.GetMap(level), m_maps.GetCurrHeight(level), m_maps.GetCurrWidth(level));
	m_curr_map = temp ;
	Hud hud(&m_score, m_curr_map.GetPlayer(), level);
	m_hud = hud;
}
//-----------------------------------------------------------------------------


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
	m_enemy_cont->set_paths();
	m_player_cont->set_paths();
}

void Game::handle_event(float dt)
{
	m_enemy_cont->move_enemies(dt);
	m_player_cont->MovePlayer(dt);
}