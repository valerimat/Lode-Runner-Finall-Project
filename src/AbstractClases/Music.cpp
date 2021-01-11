#include "Music.h"

Music::Music()
{
	LoadBuffers();
}

void Music::LoadBuffers()
{
	auto buffer_ptr = std::make_shared<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("eating laffa.OGG");
	m_buffers.push_back(buffer_ptr);
}


void Music::EaitngSound()
{
	m_sound = new sf::Sound;
	m_sound->setBuffer(*m_buffers[0]);
	m_sound->play();
}