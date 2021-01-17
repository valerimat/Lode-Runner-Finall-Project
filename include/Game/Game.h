#pragma once
#include "Map.h"
#include "MapData.h"
#include "EnemyController.h"
#include "PlayerController.h"
#include "Hud.h"
#include <SFML/Graphics.hpp>
#include "Score.h"
#include "State.h"

class Game : public State
{
public:

	// c-tors
	Game();
	void init_controllers();

	//base functions:
	void Load() override;
	void Draw(sf::RenderWindow& window) override;
	void on_update() override;
	void handle_event(float dt)override;

	void reset_level();
	void reset_game();

	//states:
	void set_prev_state(State* state);
	State* get_next_state()override;
	void set_next_state(ButtonNames  screen) override;
	bool satate_changed();
	StateEnum get_state() { return StateEnum::Game; };

	// getters
	Map* get_curr_map();
	
private:
	void advance_level();

	void check_release();
	void check_preseed_now();
	sf::Keyboard::Key was_pressed;

	//members
	int level = 0;
	Score &m_score = Score::GetScore();
	MapData m_maps;
	Map m_curr_map;
	Hud  m_hud;

	std::shared_ptr <EnemyController> m_enemy_cont;
	std::shared_ptr <PlayerController> m_player_cont;
};