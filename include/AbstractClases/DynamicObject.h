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

	bool is_on_ground(Map& map);
	bool is_on_ladder(Map& map);
	bool is_on_pole(Map& map);
	bool is_on_wall(Map& map);
	bool is_on_air(Map& map);
	bool is_on_coin(Map& map);

	sf::Vector2f get_location();
	void update_location(NextStep step);
	float get_width();
	float get_height();

protected:
	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;
	MovementController *m_controller = nullptr;
};