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
				if (event.key.code == sf::Keyboard::Up)
				{
					std::cout << "Up was pressed\n";
					std::cout << "X - " << map.get_player()->get_location().x <<
						        " Y - " << map.get_player()->get_location().y << std::endl;
					sf::Vector2f test;
					test.x = 2;
					test.y = 3;
					map.get_player()->set_location(test);

					std::cout << "X - " << map.get_player()->get_location().x <<
						        " Y - " << map.get_player()->get_location().y << std::endl;
				}
			}
		}
	}
}
