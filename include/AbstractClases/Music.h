#pragma once

#include "Macros.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Music
{
public:
	static Music& GetMusic() { static Music s_music; return s_music; };

	void LoadBuffers();

	void EaitngSound();
	void DrinkingSound();
	void RunningSound();
	void LadderSound();
	void RopeSound();
	void HurtSound();
	void BustedSound();
	void StopSound();

private:
	Music();

	// avoids copy 
	Music(const Music&) = delete;
	void operator=(Music const&) = delete;

	sf::Sound* m_sound = new sf::Sound;
	std::vector<std::shared_ptr<sf::SoundBuffer>>  m_buffers;
};
