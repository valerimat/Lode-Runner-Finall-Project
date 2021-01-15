#include "Game.h"
#include "MainMenu.h"
#include "InGameMenu.h"

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

	Hud hud(m_curr_map.GetPlayer(), level, m_curr_map.GetTimer());
	m_hud = hud;
}
//-----------------------------------------------------------------------------
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
	m_enemy_cont->set_paths();
}

void Game::handle_event(float dt)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_enemy_cont->move_enemies(dt);
		m_player_cont->MovePlayer(dt);
	}
	else
	{
		set_next_state(ButtonNames::InGameMenu);
	}
}

void  Game::set_next_state(ButtonNames next_state)
{
	State * next;
	switch (next_state)
	{
	case ButtonNames::InGameMenu:
		next = new InGameMenu;
		next->set_prev_state(this);
		sate_changed  = true;
		next_screen = next;
		break;
	}
}

bool Game::satate_changed()
{
	return sate_changed;
}