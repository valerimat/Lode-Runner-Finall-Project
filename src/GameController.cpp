#include "GameController.h"



void GameController::Run()
{
	sf::Event event;
	sf::RenderWindow main_window(sf::VideoMode (WIDTH, HEIGHT),"Lode Runner");

	Map map;
	Game game(map);
	Screens screen(game);
	EnemyController enemy_cont(map);

	while (main_window.isOpen())
	{
		
		main_window.clear(sf::Color::Black);

		//need switch case
		enemy_cont.move_enemies(map);

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
	}
}
