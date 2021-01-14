#pragma once

#include "Macros.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Music
{
public:
	Music();
	void LoadBuffers();
	void EaitngSound();
	void DrinkingSound();
	void RunningSound();
	void LadderSound();
private:

	sf::Sound* m_sound = new sf::Sound;
	std::vector<std::shared_ptr<sf::SoundBuffer>>  m_buffers;
};
