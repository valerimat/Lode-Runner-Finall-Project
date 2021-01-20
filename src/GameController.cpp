#include "GameController.h"
#include "MacroSettings.h"
#include "Clock.h"


void GameController::Run()
{
	using clock = std::chrono::high_resolution_clock;
	auto& settings = MacroSettings::GetSettings(); // inits the singelton of the settings

	sf::Event event;
	sf::Keyboard::Key keypress;

	State* screen = new MainMenu;

	sf::RenderWindow main_window(sf::VideoMode(settings.GetWidth(), settings.GetHeight()), "Lode Runner");

	// music theme song
	sf::Music music;
	music.openFromFile("game theme.OGG");
	music.setVolume(1);
	music.play();

	//-----------------

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

		OnUpdate(last, screen);
	}
}
//-----------------------------------------------------------------------------


void GameController::OnUpdate(std::chrono::steady_clock::time_point & last,State *& screen )
{
	using clock = std::chrono::high_resolution_clock;

	if (!screen->satate_changed())
	{
		//need to setup function screen->on_update();
		screen->on_update();

		auto now = clock::now();

		auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);

		//need to setup function for this one to or check type
		float dt_long = dt.count() * 0.1f;

		if (dt_long == 0)
			dt_long = 1;

		screen->handle_event(dt_long);

		last = now;
	}
	else
	{
		screen = screen->get_next_state();
	}
}

