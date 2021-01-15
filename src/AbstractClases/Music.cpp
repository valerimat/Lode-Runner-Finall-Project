#include "Music.h"
#include <iostream>

Music::Music()
{
	LoadBuffers();
}

void Music::LoadBuffers()
{
	auto buffer_ptr = std::make_shared<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("eating laffa.OGG");
	m_buffers.push_back(buffer_ptr);

	buffer_ptr = std::make_shared<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("running.ogg");
	m_buffers.push_back(buffer_ptr);

	buffer_ptr = std::make_shared<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("drinking.ogg");
	m_buffers.push_back(buffer_ptr);

	buffer_ptr = std::make_shared<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("ladder.ogg");
	m_buffers.push_back(buffer_ptr);

	buffer_ptr = std::make_shared<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("rope.ogg");
	m_buffers.push_back(buffer_ptr);
}


void Music::EaitngSound()
{
	m_sound->setBuffer(*m_buffers[0]);
	m_sound->setVolume(10);
	m_sound->play();
}

void Music::RunningSound()
{
	sf::Sound::Status status = m_sound->getStatus();
	if (status == sf::Sound::Status::Stopped)
	{
		m_sound->setBuffer(*m_buffers[1]);
		m_sound->setVolume(5);
		m_sound->play();
	}
}

void Music::DrinkingSound()
{
	m_sound->setBuffer(*m_buffers[2]);
	m_sound->setVolume(50);
	m_sound->play();
}

void Music::LadderSound()
{
	sf::Sound::Status status = m_sound->getStatus();
	if (status == sf::Sound::Status::Stopped)
	{
		m_sound->setBuffer(*m_buffers[3]);
		m_sound->setVolume(40);
		m_sound->play();
	}

}

void Music::RopeSound()
{
	sf::Sound::Status status = m_sound->getStatus();
	if (status == sf::Sound::Status::Stopped)
	{
		m_sound->setBuffer(*m_buffers[4]);
		m_sound->setVolume(50);
		m_sound->play();
	}
}


/*
void Music::StopSound()
{
	m_sound = new sf::Sound;
	m_sound->setBuffer(*m_buffers[1]);
	m_sound->setVolume(5);
	m_sound->stop();
}
*/