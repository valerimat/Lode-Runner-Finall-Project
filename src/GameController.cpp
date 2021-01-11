#include "GameController.h"

void GameController::Run()
{
	using clock = std::chrono::high_resolution_clock;

	sf::Event event;
	sf::RenderWindow main_window(sf::VideoMode(WIDTH, HEIGHT), "Lode Runner");
	sf::Music music;
	sf::Keyboard::Key keypress;

	Screens* screen = new Game;

	// music theme song 
	music.openFromFile("game theme.OGG");
	music.setVolume(1);
	music.play();

	//Screens* screen = new MainMenu;

	auto last = clock::now();

	while (main_window.isOpen())
	{
		
		keypress = sf::Keyboard::Key::End;

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
				screen->on_update();
				//need to setup function for this one to or check type
				float dt_long = dt.count();

				screen->handle_event(keypress, dt_long);
				
				last = now;
			}	
	}
}
//-----------------------------------------------------------------------------

