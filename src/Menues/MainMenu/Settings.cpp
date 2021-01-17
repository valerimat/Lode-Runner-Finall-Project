#include "Settings.h"
#include "Game.h"	

Settings::Settings() 
{
	my_state = (StateEnum::Settings);
	next_state = (StateEnum::Settings);
	load_textures();
	load_background();
	load_buttons();
	load_arrow();
	set_prev_state(nullptr);
	
}

void Settings::Load()
{

}

void Settings::on_update()
{

};

void Settings::handle_event(float dt)
{
	check_preseed_now();
	check_release();
}

void  Settings::set_next_state(ButtonNames next_state)
{
	switch (next_state)
	{
	case ButtonNames::Back:
		if (m_previouse_screen != nullptr)
			sate_changed = true;
		next_screen = m_previouse_screen;
		break;
	}
}

bool Settings::satate_changed()
{
	return sate_changed;
}

void Settings::load_textures()
{
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("arrow.png");
	m_textures.push_back(texture);

}

void Settings::load_background()
{

}
void Settings::load_buttons()
{


}
void Settings::load_arrow()
{
	
}