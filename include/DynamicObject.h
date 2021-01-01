#pragma once
#include "Macros.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
#include "MovementController.h"

class DynamicObject : public Object
{
public:
	virtual ~DynamicObject()= default;
	using Object::Object;
	void Draw(sf::RenderWindow &window);
	void set_texture(std::shared_ptr<sf::Texture> texture);
	void set_sprite();

protected:
	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;
	MovementController *m_controller = nullptr;

};