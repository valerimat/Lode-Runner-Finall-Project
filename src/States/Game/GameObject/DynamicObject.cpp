#include "DynamicObject.h"
#include "Map.h"
#include "RigidBodyObject.h"
#include "Player.h"
#include "Enemy.h"
#include "MacroSettings.h"
#include "Ladder.h"

//=============================================================================
DynamicObject::DynamicObject(char name, sf::Vector2f locaiton, sf::Texture* texture) :
	Object(name, locaiton)
{
	set_sprite(texture);
	m_size_of_tile = MacroSettings::get_settings().get_size_of_tile();
}
//=============================================================================

//=============================================================================
void DynamicObject::set_sprite(sf::Texture* texture)
{
	
	m_sprite.setTexture(*texture);
	sf::IntRect rect_sprite(0, 0, 50, 50);
	m_sprite.setTextureRect(rect_sprite);
	m_sprite.setScale(1, 1);
	m_sprite.setScale(
		sf::Vector2f(MacroSettings::get_settings().get_scale_width(),
			         MacroSettings::get_settings().get_scale_height()));

}
//=============================================================================

//=============================================================================
void DynamicObject::gravity(float dt)
{
	if(m_gravity == true)
	update_location(NextStep::DOWN, dt);
}
//=============================================================================

//=============================================================================
sf::Vector2f DynamicObject::get_location()
{
	return m_sprite.getPosition();
}
//=============================================================================

//=============================================================================
void DynamicObject::turn_gravity_on()
{
	m_gravity = true;
}
//=============================================================================

//=============================================================================
void DynamicObject::Draw(sf::RenderWindow &main_window)
{
	main_window.draw(m_sprite);
	//main_window.draw(rect);
}
//=============================================================================

//=============================================================================
void DynamicObject::update_location(NextStep step,float dt)
{
	sf::Vector2f loc = m_sprite.getPosition();

	Animation(step, this->get_name());

	float size_of_step = m_size_of_tile * 0.025f;

	switch (step)
	{
	case NextStep::LEFT:
		m_sprite.move(dt * sf::Vector2f(-size_of_step, 0));
		break;
	case NextStep::RIGHT:
		m_sprite.move(dt * sf::Vector2f(size_of_step, 0));
		break;
	case NextStep::UP:
		m_sprite.move(dt * sf::Vector2f(0, -size_of_step));
		break;
	case NextStep::DOWN:
		m_sprite.move(dt * sf::Vector2f(0, size_of_step));
		break;
	default:
		break;
	}
	last_move = loc - m_sprite.getPosition();
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(Object& object)
{
	object.handle_collision(*this);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(DynamicObject& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(StaticObject& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(RigidBodyObject& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(Player& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(Coin& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(Present& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(Enemy& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(Ladder& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::handle_collision(Pole& object)
{
	(*this).handle_collision(object);
}
//=============================================================================

//=============================================================================
void DynamicObject::move_back(RigidBodyObject &object)
{
	sf::Vector2f loc = m_sprite.getPosition();

	loc += last_move;	
	

	m_sprite.setPosition(loc);
}
//=============================================================================

//=============================================================================
void DynamicObject::move_back(Enemy& object)
{
	sf::Vector2f loc = m_sprite.getPosition();
	
	loc += last_move;
	
	m_sprite.setPosition(loc);
}
//=============================================================================

//=============================================================================
void DynamicObject::on_pole(sf::Vector2f location)
{
	if (abs (get_location().y -location.y) < m_size_of_tile*0.5f)
		m_gravity = false;
}
//=============================================================================

//=============================================================================
void DynamicObject::Animation(NextStep step, char name)
{
	auto mill_seconds = Clock::get_clock().get_passed_mill_seconds();

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
		break;

	default:
		sf::IntRect rect_sprite(0, 0, 50, 50);
		m_sprite.setTextureRect(rect_sprite);
		break;
	}
}
//=============================================================================

//=============================================================================
void  DynamicObject::reset_position()
{
	m_sprite.setPosition(m_base_location);
}
//=============================================================================

//=============================================================================
bool DynamicObject::is_in_hole()
{
	return m_in_hole;
}
//=============================================================================

//=============================================================================
void DynamicObject::SetInHole(bool IsInHole)
{
	m_in_hole = IsInHole;
}
//=============================================================================

//=============================================================================
void DynamicObject::GoInsideHole(sf::Vector2f  location)
{
	m_sprite.setPosition(
	location
	+
	sf::Vector2f(0, -m_size_of_tile * 0.9f));
}
//=============================================================================

//=============================================================================
void DynamicObject::collide_with_rigid_body(RigidBodyObject & object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
	{
		if (inter.height >= m_size_of_tile /10.f 
			&&
			inter.width >= m_size_of_tile /10.f)
		{
			move_back(object);

			if (object.IsHole())
			{
				m_in_hole = true;
				GoInsideHole(object.get_sprite().getPosition());
			}
			else
			{
				m_in_hole = false;
			}
		}
	}
}
//=============================================================================

//=============================================================================
void DynamicObject::collide_with_ladder(Ladder & object)
{
	sf::FloatRect inter;
	if (get_sprite().getGlobalBounds().intersects(object.get_sprite().getGlobalBounds(), inter))
		if (inter.width >= m_size_of_tile/8.f)
			m_gravity = false;
}
//=============================================================================

//=============================================================================
void DynamicObject::reset_after_hole()
{}
//=============================================================================
