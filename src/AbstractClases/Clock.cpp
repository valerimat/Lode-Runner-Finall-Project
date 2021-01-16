#include "Clock.h"

Clock::Clock()
{
	sf::Clock m_clock; // starts the clock
}

// gets the passed time since the clock is init
int Clock::GetPassedSeconds()
{
	float seconds;
	m_time = m_clock.getElapsedTime();
	seconds = m_time.asSeconds();

	return (int)seconds;
}

float Clock::GetPassedSecondsFloat()
{
	float seconds;
	m_time = m_clock.getElapsedTime();
	seconds = m_time.asSeconds();

	return seconds;
}

float Clock::GetPassedMillSeconds()
{
	float seconds;
	m_time = m_clock.getElapsedTime();
	seconds = m_time.asSeconds();

	return seconds - (int)seconds;
}

// restarts the clock
void Clock::RestartTime()
{
	m_clock.restart();
}
