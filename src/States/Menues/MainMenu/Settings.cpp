#include "Settings.h"
#include "Game.h"	


Settings::Settings(State * prev)
{

	load_textures();
	load_background();
	load_buttons();
	load_arrow();

}

void Settings::load()
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



bool Settings::satate_changed()
{
	return sate_changed;
}

void Settings::load_textures()
{
	auto texture = new sf::Texture;
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