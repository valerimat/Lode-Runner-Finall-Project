#include "GameController.h"



void GameController::Run()
{
	using clock = std::chrono::high_resolution_clock;

	sf::Event event;
	sf::RenderWindow main_window(sf::VideoMode (WIDTH, HEIGHT),"Lode Runner");

	Map map;
	Game game(map);
	Screens screen(game);
	EnemyController enemy_cont(map);
	PlayerController player_controller(map);

	auto last = clock::now();

	while (main_window.isOpen())
	{
		auto now = clock::now();

		auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);


		

			main_window.clear(sf::Color::Black);
			if (dt.count() >= (long long)30)
			{
				last = now;
				//need switch case
				enemy_cont.move_enemies(map);
			}
			screen.Draw(main_window);

			main_window.display();
		
		

		while (main_window.pollEvent(event))
		{
			switch (event.type)
			{
			case(sf::Event::Closed):
				main_window.close();
				break;
			case(sf::Event::KeyPressed):
				if (event.key.code == sf::Keyboard::Up   ||
					event.key.code == sf::Keyboard::Down ||
					event.key.code == sf::Keyboard::Left ||
					event.key.code == sf::Keyboard::Right)
				{
					player_controller.move_player(event.key.code);
				}
			}
		}
	}
}
