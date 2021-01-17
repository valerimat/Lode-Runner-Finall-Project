#include "DynamicObject.h"
#include "Map.h"
#include "RigidBodyObject.h"

DynamicObject::DynamicObject(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture) :
	Object(name, locaiton)
{
	set_sprite(texture);
}
//-----------------------------------------------------------------------------

void DynamicObject::set_sprite(std::shared_ptr<sf::Texture> texture)
{
	
	m_sprite.setTexture(*texture);
	sf::IntRect rect_sprite(0, 0, 50, 50);
	m_sprite.setTextureRect(rect_sprite);
	m_sprite.setScale(sf::Vector2f(0.8, 0.8));

}
//-----------------------------------------------------------------------------

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
//-----------------------------------------------------------------------------

void DynamicObject::Draw(sf::RenderWindow &main_window)
{
	main_window.draw(m_sprite);
}
//-----------------------------------------------------------------------------

void DynamicObject::update_location(NextStep step,float dt)
{
	sf::Vector2f loc = m_sprite.getPosition();
	auto mill_seconds = Clock::GetClock().GetPassedMillSeconds();

	Animation(step, this->get_name());

	switch (step)
	{
	case NextStep::LEFT:
		m_sprite.move(dt * sf::Vector2f(-STEP, 0));
		break;
	case NextStep::RIGHT:
		m_sprite.move(dt * sf::Vector2f(STEP, 0));
		break;
	case NextStep::UP:
		m_sprite.move(dt * sf::Vector2f(0, -STEP));
		break;
	case NextStep::DOWN:
		m_sprite.move(dt * sf::Vector2f(0, STEP));
		break;
	default:
		break;
	}
	last_move = loc - m_sprite.getPosition();
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(Object& object)
{
	object.handle_collision(*this);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(DynamicObject& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(StaticObject& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(RigidBodyObject& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(Player& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(Coin& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(Present& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(Enemy& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(Ladder& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::handle_collision(Pole& object)
{
	(*this).handle_collision(object);
}
//-----------------------------------------------------------------------------

void DynamicObject::move_back(RigidBodyObject &object)
{
	sf::Vector2f loc = m_sprite.getPosition();
	if (object.m_hole == false)
	{
		loc += last_move;	
	}
	else
	{
		loc += last_move;
		sf::FloatRect rect;
		m_sprite.getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), rect);
		loc += sf::Vector2f(0, -rect.height);
	}
	m_sprite.setPosition(loc);
}
//-----------------------------------------------------------------------------

void DynamicObject::on_pole(sf::Vector2f location)
{
	if (abs (get_location().y -location.y) < 5)
		m_gravity = false;
}
//-----------------------------------------------------------------------------

void DynamicObject::Animation(NextStep step, char name)
{
	auto mill_seconds = Clock::GetClock().GetPassedMillSeconds();

	switch (step)
	{
	case NextStep::LEFT:

		if (mill_seconds < 0.25)
		{
			sf::IntRect rect_sprite(0, 100, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		else if (mill_seconds > 0.25 && mill_seconds < 0.5)
		{
			sf::IntRect rect_sprite(50, 100, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		else if (mill_seconds > 0.5 && mill_seconds < 0.75)
		{
			sf::IntRect rect_sprite(100, 100, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		else
		{
			sf::IntRect rect_sprite(150, 100, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}

		break;

	case NextStep::RIGHT:
		if (mill_seconds < 0.25)
		{
			sf::IntRect rect_sprite(0, 50, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		else if (mill_seconds > 0.25 && mill_seconds < 0.5)
		{
			sf::IntRect rect_sprite(50, 50, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		else if (mill_seconds > 0.5 && mill_seconds < 0.75)
		{
			sf::IntRect rect_sprite(100, 50, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		else
		{
			sf::IntRect rect_sprite(150, 50, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		break;

	case NextStep::UP:
		if (mill_seconds < 0.5)
		{
			sf::IntRect rect_sprite(150, 150, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		else
		{
			sf::IntRect rect_sprite(100, 150, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		break;

	case NextStep::DOWN:
		/*
		if (mill_seconds < 0.5)
		{
			sf::IntRect rect_sprite(150, 150, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		else
		{
			sf::IntRect rect_sprite(100, 150, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}
		*/
		break;

	default:
		sf::IntRect rect_sprite(0, 0, 50, 50);
		m_sprite.setTextureRect(rect_sprite);
		break;
	}
}
