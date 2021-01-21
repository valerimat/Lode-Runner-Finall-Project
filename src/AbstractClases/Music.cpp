#include "Music.h"
#include <iostream>
#include "MacroSettings.h"

//=============================================================================
Music::Music()
{
	load_buffers();
}

Music::~Music()
{
	for (int i = 0; i < m_buffers.size(); i++)
	{
		delete &m_buffers[i];
	}
}

//=============================================================================

//=============================================================================
void Music::load_buffers()
{
	// eating sound
	auto buffer_ptr = new sf::SoundBuffer;
	buffer_ptr->loadFromFile("eating laffa.OGG");

	m_buffers.push_back(*buffer_ptr);

	buffer_ptr = new sf::SoundBuffer;
	buffer_ptr->loadFromFile("running.OGG");

	m_buffers.push_back(*buffer_ptr);

	buffer_ptr = new sf::SoundBuffer;
	buffer_ptr->loadFromFile("drinking.OGG");

	m_buffers.push_back(*buffer_ptr);

	buffer_ptr = new sf::SoundBuffer;
	buffer_ptr->loadFromFile("ladder.OGG");

	m_buffers.push_back(*buffer_ptr);

	buffer_ptr = new sf::SoundBuffer;
	buffer_ptr->loadFromFile("rope.OGG");

	m_buffers.push_back(*buffer_ptr);

	buffer_ptr = new sf::SoundBuffer;
	buffer_ptr->loadFromFile("hurt.OGG");

	m_buffers.push_back(*buffer_ptr);

	buffer_ptr = new sf::SoundBuffer;
	buffer_ptr->loadFromFile("busted.OGG");

	m_buffers.push_back(*buffer_ptr);

	/*
	// running sounds
	buffer_ptr = std::make_unique<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("running.ogg.OGG");

	std::vector<std::unique_ptr<sf::SoundBuffer>> get_dynamic();
	m_buffers.push_back(
		std::make_unique<sf::SoundBuffer>(buffer_ptr));

	// drinking sound
	buffer_ptr = std::make_unique<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("drinking.ogg");

	std::vector<std::unique_ptr<sf::SoundBuffer>> get_dynamic();
	m_buffers.push_back(
		std::make_unique<sf::SoundBuffer>(buffer_ptr));

	// ladder sound
	buffer_ptr = std::make_unique<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("ladder.ogg");

	std::vector<std::unique_ptr<sf::SoundBuffer>> get_dynamic();
	m_buffers.push_back(
		std::make_unique<sf::SoundBuffer>(buffer_ptr));

	// rope sound
	buffer_ptr = std::make_unique<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("rope.ogg");

	std::vector<std::unique_ptr<sf::SoundBuffer>> get_dynamic();
	m_buffers.push_back(
		std::make_unique<sf::SoundBuffer>(buffer_ptr));

	// hurt sound
	buffer_ptr = std::make_unique<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("hurt.ogg");

	std::vector<std::unique_ptr<sf::SoundBuffer>> get_dynamic();
	m_buffers.push_back(
		std::make_unique<sf::SoundBuffer>(buffer_ptr));

	// busted sound
	buffer_ptr = std::make_unique<sf::SoundBuffer>();
	buffer_ptr->loadFromFile("busted.ogg");

	std::vector<std::unique_ptr<sf::SoundBuffer>> get_dynamic();
	m_buffers.push_back(
		std::make_unique<sf::SoundBuffer>(buffer_ptr));
	*/
}
//=============================================================================

//=============================================================================
void Music::eating_sound()
{
	m_sound->setBuffer(m_buffers[0]);
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
		m_sound->setBuffer(m_buffers[1]);
		m_sound->setVolume(MacroSettings::get_settings().get_volume()/ 10);
		m_sound->play();
	}
}
//=============================================================================

//=============================================================================
void Music::drinking_sound()
{
	m_sound->setBuffer(m_buffers[2]);
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
		m_sound->setBuffer(m_buffers[3]);
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
		m_sound->setBuffer(m_buffers[4]);
		m_sound->setVolume(MacroSettings::get_settings().get_volume());
		m_sound->play();
	}
}
//=============================================================================

//=============================================================================
void Music::hurt_sound()
{
	m_sound->setBuffer(m_buffers[5]);
	m_sound->setVolume(MacroSettings::get_settings().get_volume());
	m_sound->play();
}
//=============================================================================

//=============================================================================
void Music::busted_sound()
{
	m_sound->setBuffer(m_buffers[6]);
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