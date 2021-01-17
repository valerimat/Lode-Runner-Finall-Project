#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Present.h"

StaticObject::StaticObject(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture):
Object(name,locaiton)
{
	set_sprite(texture);
}
//-----------------------------------------------------------------------------

void StaticObject::set_sprite(std::shared_ptr<sf::Texture> texture)
{
	m_sprite.setTexture(*texture);
	m_sprite.setScale(sf::Vector2f(0.8, 0.8));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

void StaticObject::Draw(sf::RenderWindow & main_window)
{
	main_window.draw(m_sprite);
}
//-----------------------------------------------------------------------------

bool StaticObject::in_bounds(sf::Vector2f &location)
{
	if (m_sprite.getGlobalBounds().contains(location))
	{	
		return true;
	}	
	return false;
}
//-----------------------------------------------------------------------------

bool StaticObject::in_bounds(sf::RectangleShape& rect)
{
	if (m_sprite.getGlobalBounds().intersects(rect.getGlobalBounds()))
		return true;
	return false;
}
//-----------------------------------------------------------------------------


//===================== Collision
void StaticObject::handle_collision(Object& object)
{
	object.handle_collision(*this);
}

void StaticObject::handle_collision(StaticObject& object)
{
	//ignore
}
void StaticObject::handle_collision(RigidBodyObject& object)
{
	//ignore
}
void StaticObject::handle_collision(Player& object)
{
	//object.handle_collision(*this);
}
void StaticObject::handle_collision(Coin & object)
{

}
void StaticObject::handle_collision(Present& object)
{

}
void StaticObject::handle_collision(Enemy& object)
{
	object.handle_collision(*this);
}

void StaticObject::handle_collision(Ladder& object)
{
	//ignore
}
void StaticObject::handle_collision(Pole& object)
{
	//ignore
}

void StaticObject::handle_collision(DynamicObject& object)
{
	object.handle_collision(*this);
}
