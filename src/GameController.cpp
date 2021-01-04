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
	Map curr_map = game.get_curr_map();
	Screens screen(game);
	EnemyController enemy_cont(curr_map);
	PlayerController player_controller(curr_map);

	auto last = clock::now();

	while (main_window.isOpen())
	{
		auto now = clock::now();

		auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);

		main_window.clear(sf::Color::Black);
		if (dt.count() >= (long long)30)
		{
			
			//need switch case
			enemy_cont.move_enemies(curr_map);


			screen.Draw(main_window);

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
				player_controller.move_player(event.key.code, curr_map);
			}
			last = now;
		}
	}
}

	/*
	case(sf::Event::KeyPressed):
				if (event.key.code == sf::Keyboard::Up ||
					event.key.code == sf::Keyboard::Down ||
					event.key.code == sf::Keyboard::Left ||
					event.key.code == sf::Keyboard::Right)
				{
					player_controller.move_player(event.key.code, map);
				}
			}
			*/