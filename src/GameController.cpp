#include "GameController.h"

void GameController::Run()
{
	using clock = std::chrono::high_resolution_clock;

	sf::Event event;
	sf::RenderWindow main_window(sf::VideoMode(WIDTH, HEIGHT), "Lode Runner");


	
	State* screen = new MainMenu;

	//Screens* screen = new MainMenu;

	auto last = clock::now();

	while (main_window.isOpen())
	{
	

		main_window.clear(sf::Color::Black);

		screen->Draw(main_window);

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
			
			auto now = clock::now();
			auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);

			if (dt.count() > 5)
			{
				if (!screen->satate_changed())
				{
					//need to setup function screen->on_update();
					screen->on_update();
					//need to setup function for this one to or check type
					float dt_long = dt.count();

					screen->handle_event(dt_long);

					last = now;
				}
				else
				{
					screen = screen->get_next_state();
				}
			}
			
	}
}
//-----------------------------------------------------------------------------

