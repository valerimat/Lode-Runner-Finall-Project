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
}
//-----------------------------------------------------------------------------

void DynamicObject::update_location(NextStep step,float dt)
{
	sf::Vector2f loc = m_sprite.getPosition();
	auto mill_seconds = Clock::GetClock().GetPassedMillSeconds();

	switch (step)
	{
	case NextStep::LEFT:
		if (this->get_name() == '@')
		{
			if (mill_seconds < 0.3)
			{
				sf::IntRect rect_sprite(0, 100, 50, 50);
				m_sprite.setTextureRect(rect_sprite);
			}
			else if (mill_seconds > 0.33 && mill_seconds < 0.66)
			{
				sf::IntRect rect_sprite(50, 100, 50, 50);
				m_sprite.setTextureRect(rect_sprite);
			}
			else
			{
				sf::IntRect rect_sprite(100, 100, 50, 50);
				m_sprite.setTextureRect(rect_sprite);
			}
		}

		m_sprite.move(dt *sf::Vector2f(-STEP, 0));
		break;
	case NextStep::RIGHT:
		if (this->get_name() == '@')
		{
			if (mill_seconds < 0.3)
			{
				sf::IntRect rect_sprite(0, 50, 50, 50);
				m_sprite.setTextureRect(rect_sprite);
			}
			else if (mill_seconds > 0.33 && mill_seconds < 0.66)
			{
				sf::IntRect rect_sprite(50, 50, 50, 50);
				m_sprite.setTextureRect(rect_sprite);
			}
			else
			{
				sf::IntRect rect_sprite(100, 50, 50, 50);
				m_sprite.setTextureRect(rect_sprite);
			}
		}

		m_sprite.move(dt *sf::Vector2f(STEP, 0));
		break;
	case NextStep::UP:
		if (this->get_name() == '@')
		{
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
		}

		m_sprite.move(dt *sf::Vector2f(0,-STEP));
		break;
	case NextStep::DOWN:
		if (this->get_name() == '@')
		{
			//sf::IntRect rect_sprite(150, 150, 50, 50);
			//m_sprite.setTextureRect(rect_sprite);
		}

		m_sprite.move(dt * sf::Vector2f(0, STEP));
		break;
	default:
		if (this->get_name() == '@')
		{
			sf::IntRect rect_sprite(0, 0, 50, 50);
			m_sprite.setTextureRect(rect_sprite);
		}

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
