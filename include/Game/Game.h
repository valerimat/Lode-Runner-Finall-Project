#pragma once
#include "Map.h"
#include "MapData.h"
#include "EnemyController.h"
#include "PlayerController.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>
#include "Score.h"
#include "Screens.h"

class Game : public Screens
{
public:

	// c-tors
	Game();
	void init_controllers();
	

	// getters
	Map* get_curr_map();
	
	// Game functions
	void Load() override;
	void Draw(sf::RenderWindow& window) override;
	void on_update() override;
	void handle_event( float dt)override;
	Screens* get_next_state()override { return NULL; };
	void set_next_state(State next) override {};
	bool satate_changed() { return false; };
private:

	//members
	int level = 0;
	Score m_score;
	MapData m_maps;
	Map m_curr_map;
	Hud  m_hud;
	std::shared_ptr <EnemyController> m_enemy_cont;
	std::shared_ptr <PlayerController> m_player_cont;
};