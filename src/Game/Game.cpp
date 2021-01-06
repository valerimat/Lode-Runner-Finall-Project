#include "Game.h"

Game::Game(MapData& maps) :
	m_maps(maps)
{
}

void Game::Load_level()
{
	Map temp(m_maps.get_map(level), m_maps.get_curr_height(level), m_maps.get_curr_width(level));
	m_curr_map = temp ;
	Hud hud(&m_score, m_curr_map.get_player(), level);
	m_hud = hud;
}

void Game::InitHud()
{
	
}

void Game::Draw(sf::RenderWindow &window)
{
	m_curr_map.Draw(window);
	m_hud.Draw(window);
}

Map * Game::get_curr_map()
{
	return & m_curr_map;
}