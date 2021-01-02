#include "Game.h"

Game::Game(Map & map):
m_map(map)
//, m_hud(hud)
{
}

void Game::Draw(sf::RenderWindow &window)
{
	m_map.Draw(window);
	//m_hud.Draw();
}