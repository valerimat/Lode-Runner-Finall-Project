 #include "Menu.h"

void Menu::set_prev_state(State* prev_screen)
{
	m_previouse_screen = prev_screen;
}


State* Menu::get_next_state()
{
	sate_changed = false;
	return next_screen;
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(background);

	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].Draw(window);

	m_arrow.Draw(window);

	
};


void Menu::check_release()
{
	if (was_pressed == sf::Keyboard::Enter && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
	{
		set_next_state(m_buttons[index_of_selected_button].get_name());
		was_pressed = sf::Keyboard::Unknown;
	}
	if (was_pressed == sf::Keyboard::Up && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
	{
		index_of_selected_button = (index_of_selected_button - 1) % m_buttons.size();
		m_arrow.move_arrow(m_buttons[index_of_selected_button].get_location());
		was_pressed = sf::Keyboard::Unknown;
	}
	if (was_pressed == sf::Keyboard::Down && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		index_of_selected_button = (index_of_selected_button + 1) % m_buttons.size();
		m_arrow.move_arrow(m_buttons[index_of_selected_button].get_location());
		was_pressed = sf::Keyboard::Unknown;
	}
	if (was_pressed == sf::Keyboard::Escape && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
	{
		if (m_previouse_screen != nullptr)
			set_next_state(ButtonNames::Back);

		was_pressed = sf::Keyboard::Unknown;
	}
}

void Menu::check_preseed_now()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		was_pressed = sf::Keyboard::Enter;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		was_pressed = sf::Keyboard::Escape;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		was_pressed = sf::Keyboard::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		was_pressed = sf::Keyboard::Up;
	}
}