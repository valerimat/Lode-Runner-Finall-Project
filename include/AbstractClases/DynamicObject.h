#pragma once
#include "Macros.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
#include "MovementController.h"

class Map;

class DynamicObject : public Object
{
public:
	//virtual ~DynamicObject() = default;
	using Object::Object;
	virtual void init_object(char  m_name, sf::Vector2f  m_location);
	void Draw(sf::RenderWindow &window);
	void set_texture(std::shared_ptr<sf::Texture> texture);
	void set_sprite();
	bool in_bounds(sf::Vector2f &location);


	std::vector<char> is_on_something(Map& map, sf::Keyboard::Key key);

	sf::Vector2f get_location();
	sf::Vector2f get_next_location(sf::Keyboard::Key key);
	void update_location(NextStep step);
	float get_width();
	float get_height();
	sf::Sprite get_sprite();

protected:
	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;
	MovementController *m_controller = nullptr;
};