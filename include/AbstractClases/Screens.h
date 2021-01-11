#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

class Screens
{
public:
	Screens() = default;
	virtual void on_update() = 0;
	virtual void Load() = 0;
	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void handle_event(float dt) = 0;
	virtual void set_next_state(State next) = 0;
	virtual Screens* get_next_state() = 0;
	virtual bool satate_changed() = 0;
	
protected:
	Screens* next_screen;
};