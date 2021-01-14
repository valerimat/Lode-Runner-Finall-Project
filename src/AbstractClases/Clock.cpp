#include "Clock.h"

Clock::Clock()
{
	sf::Clock m_time; // starts the clock
}

// gets the passed time since the clock is init
int Clock::GetPassedTime()
{
	sf::Time time;
	float seconds;
	time = m_time.getElapsedTime();
	seconds = time.asSeconds();

	return (int)seconds;
}

// restarts the clock
void Clock::RestartTime()
{
	m_time.restart();
}
