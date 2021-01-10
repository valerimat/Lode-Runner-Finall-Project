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
	virtual void handle_event(sf::Keyboard::Key, float dt) = 0;

private:

};