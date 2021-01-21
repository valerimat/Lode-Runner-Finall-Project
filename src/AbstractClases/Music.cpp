#include "Music.h"
#include <iostream>
#include "MacroSettings.h"

//=============================================================================
Music::Music()
{
	load_buffers();
}
//=============================================================================

//=============================================================================
void Music::load_buffers()
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

	buffer_ptr = std::make_shared<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("hurt.ogg");
	m_buffers.push_back(buffer_ptr);

	buffer_ptr = std::make_shared<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("busted.ogg");
	m_buffers.push_back(buffer_ptr);
}
//=============================================================================

//=============================================================================
void Music::eating_sound()
{
	m_sound->setBuffer(*m_buffers[0]);
	m_sound->setVolume(MacroSettings::get_settings().get_volume()/ 5);
	m_sound->play();
}
//=============================================================================

//=============================================================================
void Music::running_sound()
{
	sf::Sound::Status status = m_sound->getStatus();

	if (status == sf::Sound::Status::Stopped)
	{
		m_sound->setBuffer(*m_buffers[1]);
		m_sound->setVolume(MacroSettings::get_settings().get_volume()/ 10);
		m_sound->play();
	}
}
//=============================================================================

//=============================================================================
void Music::drinking_sound()
{
	m_sound->setBuffer(*m_buffers[2]);
	m_sound->setVolume(MacroSettings::get_settings().get_volume());
	m_sound->play();
}
//=============================================================================

//=============================================================================
void Music::ladder_sound()
{
	sf::Sound::Status status = m_sound->getStatus();
	if (status == sf::Sound::Status::Stopped)
	{
		m_sound->setBuffer(*m_buffers[3]);
		m_sound->setVolume(MacroSettings::get_settings().get_volume());
		m_sound->play();
	}
}
//=============================================================================

//=============================================================================
void Music::rope_sound()
{
	sf::Sound::Status status = m_sound->getStatus();
	if (status == sf::Sound::Status::Stopped)
	{
		m_sound->setBuffer(*m_buffers[4]);
		m_sound->setVolume(MacroSettings::get_settings().get_volume());
		m_sound->play();
	}
}
//=============================================================================

//=============================================================================
void Music::hurt_sound()
{
	m_sound->setBuffer(*m_buffers[5]);
	m_sound->setVolume(MacroSettings::get_settings().get_volume());
	m_sound->play();
}
//=============================================================================

//=============================================================================
void Music::busted_sound()
{
	m_sound->setBuffer(*m_buffers[6]);
	m_sound->setVolume(MacroSettings::get_settings().get_volume());
	m_sound->play();
}
//=============================================================================

//=============================================================================
void Music::stop_sound()
{
	m_sound->stop();
}
//=============================================================================