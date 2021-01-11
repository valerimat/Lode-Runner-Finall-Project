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
	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].Draw(window);

	m_arrow.Draw(window);
};