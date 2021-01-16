#pragma once
#include <SFML/Graphics.hpp>

// singleton class for clock
class Clock
{
public:
	static Clock& GetClock() {static Clock s_clock; return s_clock;};

	void RestartTime();
	int GetPassedSeconds();
	float GetPassedMillSeconds();

private:
	Clock();

	// avoids copy 
	Clock(const Clock&) = delete;
	void operator=(Clock const&) = delete;

	//static Clock s_clock;
	//sf::Clock m_time;
	sf::Clock m_clock;
	sf::Time m_time;
};
