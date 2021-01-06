#include "Game.h"

Game::Game(MapData& maps) :
	m_maps(maps)
{
}
//-----------------------------------------------------------------------------

void Game::LoadLevel()
{
	Map temp(m_maps.GetMap(level), m_maps.GetCurrHeight(level), m_maps.GetCurrWidth(level));
	m_curr_map = temp ;
	Hud hud(&m_score, m_curr_map.GetPlayer(), level);
	m_hud = hud;
}
//-----------------------------------------------------------------------------

void Game::InitHud()
{
}
//-----------------------------------------------------------------------------

void Game::Draw(sf::RenderWindow &window)
{
	m_curr_map.Draw(window);
	m_hud.Draw(window);
}
//-----------------------------------------------------------------------------

Map * Game::GetCurrMap()
{
	return & m_curr_map;
}
//-----------------------------------------------------------------------------