#pragma once

#include "Macros.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Music
{
public:
	static Music& get_music() { static Music s_music; return s_music; };

	// loads all the buffers
	void load_buffers();

	// sounds
	void eating_sound();
	void drinking_sound();
	void running_sound();
	void ladder_sound();
	void rope_sound();
	void hurt_sound();
	void busted_sound();
	void stop_sound();

private:
	Music();

	// avoids copy 
	Music(const Music&) = delete;
	void operator=(Music const&) = delete;

	sf::Sound* m_sound = new sf::Sound;
	std::vector<std::shared_ptr<sf::SoundBuffer>> m_buffers;
};
