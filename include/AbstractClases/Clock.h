#pragma once
#include <SFML/Graphics.hpp>

// singleton class for clock
class Clock
{
public:

	// get singleton
	static Clock& get_clock(){static Clock s_clock; return s_clock;};

	// clock func
	void  restart_time();

	// getters
	int   get_passed_seconds();
	float get_passed_mill_seconds();
	float get_passed_seconds_float();

private:

	// c-tor
	Clock();

	// avoids copy 
	Clock(const Clock&) = delete;
	void operator=(Clock const&) = delete;

	// private members
	sf::Clock m_clock;
	sf::Time m_time;
};
