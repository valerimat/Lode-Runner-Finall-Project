#include "DynamicObject.h"
#include "Map.h"
#include "RigidBodyObject.h"

DynamicObject::DynamicObject(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture):
	Object(name, locaiton)
{
	rect.setPosition(sf::Vector2f(-1, -1));
	set_sprite(texture);
}
//-----------------------------------------------------------------------------

void DynamicObject::set_sprite(std::shared_ptr<sf::Texture> texture)
{
	
	m_sprite.setTexture(*texture);
	m_sprite.setScale(sf::Vector2f(0.8, 0.8));

}
void DynamicObject::gravity(float dt)
{
	if(m_gravity == true)
	update_location(NextStep::DOWN, dt);
}
//-----------------------------------------------------------------------------

sf::Vector2f DynamicObject::get_location()
{
	return m_sprite.getPosition();
}
//-----------------------------------------------------------------------------
void DynamicObject::turn_gravity_on()
{
	m_gravity = true;
}

void DynamicObject::Draw(sf::RenderWindow &main_window)
{
	main_window.draw(m_sprite);

	
	if (rect.getPosition() != sf::Vector2f(-1, -1))
	{
		rect.setSize(sf::Vector2f(30, 30));
		rect.setFillColor(sf::Color::Blue);
	}
	main_window.draw(rect);
	
}
//-----------------------------------------------------------------------------

void DynamicObject::update_location(NextStep step,float dt)
{
	sf::Vector2f loc = m_sprite.getPosition();
	switch (step)
	{
	case NextStep::LEFT:
		m_sprite.move(dt *sf::Vector2f(-STEP, 0));
		break;
	case NextStep::RIGHT:
		m_sprite.move(dt *sf::Vector2f(STEP, 0));
		break;
	case NextStep::UP:
		m_sprite.move(dt *sf::Vector2f(0,-STEP));
		break;
	case NextStep::DOWN:
		m_sprite.move(dt * sf::Vector2f(0, STEP));
		break;
	default:
		break;
	}
	last_move = loc - m_sprite.getPosition();
}


void DynamicObject::handle_collision(Object& object)
{
	object.handle_collision(*this);
}

void DynamicObject::move_back()
{
	sf::Vector2f loc = m_sprite.getPosition();
	loc += last_move;
	m_sprite.setPosition(loc);
}

void DynamicObject::on_pole(sf::Vector2f location)
{
	if (abs (get_location().y -location.y) < 5)
		m_gravity = false;
}
