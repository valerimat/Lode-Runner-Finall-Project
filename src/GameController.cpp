#include "GameController.h"

void GameController::Run()
{
	using clock = std::chrono::high_resolution_clock;

	sf::Event event;
	sf::RenderWindow main_window(sf::VideoMode(WIDTH, HEIGHT), "Lode Runner");

	MapData map_data;
	Game game(map_data);

	//loads level
	game.Load_level();

	//will hold curr map
	Map  * curr_map = game.get_curr_map();

	Screens screen(game);
	EnemyController enemy_cont(curr_map);
	PlayerController player_cont(curr_map);
	player_cont.InitPlayer();
	enemy_cont.init_controller();
	sf::Keyboard::Key keypress;
	auto last = clock::now();

	while (main_window.isOpen())
	{
		
		keypress = sf::Keyboard::Key::End;

		main_window.clear(sf::Color::Black);
	
		game.Draw(main_window);

		main_window.display();

		while (main_window.pollEvent(event))
		{
			switch (event.type)
			{
			case(sf::Event::Closed):
				main_window.close();
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			keypress = event.key.code;
		}
			
			auto now = clock::now();
			auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);

			if (dt.count() > 5)
			{
				//need to setup function screen->on_update();
				calculate_valid_steps(enemy_cont, player_cont);
				//need to setup function for this one to or check type
				float dt_long = dt.count();

				move_g(enemy_cont, player_cont, dt_long, keypress);

				last = now;
			}
			
	}
}
//-----------------------------------------------------------------------------

void GameController::calculate_valid_steps(EnemyController & enemy_cont, PlayerController & player_cont)
{
	enemy_cont.set_paths();
	player_cont.SetPaths();
}
//-----------------------------------------------------------------------------

void GameController::move_g(EnemyController & enemy_cont, PlayerController & player_cont, float dt, sf::Keyboard::Key keypress)
{
	enemy_cont.move_enemies(dt);
	player_cont.MovePlayer(keypress, dt);
}
//-----------------------------------------------------------------------------