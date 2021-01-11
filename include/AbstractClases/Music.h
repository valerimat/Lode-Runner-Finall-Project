#pragma once

#include "Macros.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Music
{
public:
	Music();
	void LoadBuffers();
	void EaitngSound();
private:

	sf::Sound* m_sound = nullptr;
	std::vector<std::shared_ptr<sf::SoundBuffer>>  m_buffers;
};
