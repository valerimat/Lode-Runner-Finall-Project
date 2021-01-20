#include "Clock.h"

Clock::Clock()
{
	sf::Clock m_clock; // starts the clock
}

// gets the passed time since the clock is init
int Clock::get_passed_seconds()
{
	float seconds;
	m_time = m_clock.getElapsedTime();
	seconds = m_time.asSeconds();

	return (int)seconds;
}

float Clock::get_passed_seconds_float()
{
	float seconds;
	m_time = m_clock.getElapsedTime();
	seconds = m_time.asSeconds();

	return seconds;
}

float Clock::get_passed_mill_seconds()
{
	float seconds;
	m_time = m_clock.getElapsedTime();
	seconds = m_time.asSeconds();

	return seconds - (int)seconds;
}

// restarts the clock
void Clock::restart_time()
{
	m_clock.restart();
}
