#pragma once
#include "Macros.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
class Player;
class Enemey;
class RigidBodyObject;
class Consumables;
class Pole;
class Coin;
class Present;

class StaticObject : public Object
{
public:
	using Object::Object;
	StaticObject(char Name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture);
	void Draw(sf::RenderWindow &window);
	void set_sprite(std::shared_ptr<sf::Texture> texture);
	bool in_bounds(sf::Vector2f &location);
	bool in_bounds(sf::RectangleShape& rect);

	virtual bool  make_hole() { return false; };
	//collision:
	void handle_collision(DynamicObject& object) override;
	void handle_collision(Coin& object) override;
	void handle_collision(Present& object) override;
	void handle_collision(Pole &object) override;
	void handle_collision(Ladder& object) override;
	void handle_collision(Object& object) override;
	void handle_collision(StaticObject& object)override;
	void handle_collision(RigidBodyObject& object) override;
	void handle_collision(Player& object) override;
	void handle_collision(Enemy& object) override;
	
	void SetHole(bool boolean);
	bool get_hole();

protected:
	bool m_hole = false;

};