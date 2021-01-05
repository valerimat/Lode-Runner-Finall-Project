#include "DynamicObject.h"
#include "Map.h"

void DynamicObject::set_texture(std::shared_ptr<sf::Texture> texture)
{
	m_texture = texture;
	set_sprite();
}

void DynamicObject::set_sprite()
{
	sf::Sprite sprite;
	sprite.setTexture(*m_texture);
	sprite.setPosition(m_location);
	sprite.setScale(sf::Vector2f(0.8, 0.8));
	m_sprite = sprite;
}
sf::Vector2f DynamicObject::get_location()
{
	return m_location;
}

void DynamicObject::init_object(char  m_name, sf::Vector2f  m_location)
{
	set_name(m_name);
	sf::Vector2f loc(m_location.y * OFFSET, m_location.x * OFFSET);
	set_location(loc);
}

void DynamicObject::Draw(sf::RenderWindow &main_window)
{
	main_window.draw(m_sprite);
}

bool DynamicObject::in_bounds(sf::Vector2f & location)
{
	if (m_sprite.getGlobalBounds().contains(location))
		return true;

	return false;
}



void DynamicObject::update_location(NextStep step)
{
	switch (step)
	{
	case NextStep::LEFT:
		m_sprite.move(sf::Vector2f(-STEP, 0));
		m_location.x -= STEP;
		break;
	case NextStep::RIGHT:
		m_sprite.move(sf::Vector2f(STEP, 0));
		m_location.x += STEP;
		break;
	case NextStep::UP:
		m_sprite.move(sf::Vector2f(0,-STEP));
		m_location.y -= STEP;
		break;
	case NextStep::DOWN:
		m_sprite.move(sf::Vector2f(0, STEP));
		m_location.y += STEP;
		break;
	default:
		break;
	}
}


float DynamicObject::get_width()
{
	return m_sprite.getGlobalBounds().width;
}
float DynamicObject::get_height()
{
	return m_sprite.getGlobalBounds().height;
}



bool DynamicObject::is_on_ladder(Map& map,sf::Vector2f location)
{

	
	for (int i = 0; i < (*map.get_static()).size(); i++)
	{
		if ((*map.get_static())[i]->get_name() == LADDER && (*map.get_static())[i]->in_bounds(location))
			return true;
	}
	return false;
}

bool DynamicObject::is_on_pole(Map& map)
{

	sf::Vector2f location = m_location;

	for (int i = 0; i < (*map.get_static()).size(); i++)
	{
		if ((*map.get_static())[i]->get_name() == POLE && (*map.get_static())[i]->in_bounds(location))
			return true;
	}
	return false;
}

bool DynamicObject::is_on_wall(Map& map)
{
	sf::Vector2f location_right, location_left;

	location_left = location_right = m_location;

	location_left.x += 35;

	std::vector<std::shared_ptr<StaticObject>>* static_arr = map.get_static();

	for (int i = 0; i < (*static_arr).size(); i++)
	{
		if (((*static_arr)[i]->get_name() == GROUND && (*static_arr)[i]->in_bounds(location_left)) ||
			((*static_arr)[i]->get_name() == GROUND && (*static_arr)[i]->in_bounds(location_right)))
			return true;
	}
	return false;
}

bool DynamicObject::is_on_coin(Map& map)
{
	std::vector<std::shared_ptr<StaticObject>>* static_arr = map.get_static();

	sf::Vector2f location = m_location;
	for (int i = 0; i < (*static_arr).size(); i++)
	{
		if (((*static_arr))[i]->get_name() == COIN && ((*static_arr))[i]->in_bounds(location))
			return true;
	}
	return false;
}

// gets a axis vector of the next location which is helpful to know whats a head
sf::Vector2f DynamicObject::get_next_location(sf::Keyboard::Key key)
{
	sf::Vector2f temp = m_location;

	// STEP is a const in Marcros.h
	switch (key)
	{
	case sf::Keyboard::Up:
		temp.y -= STEP;
		break;
	case sf::Keyboard::Down:
		temp.y += STEP;
		break;
	case sf::Keyboard::Left:
		temp.x -= STEP;
		break;
	case sf::Keyboard::Right:
		temp.x += STEP;
		break;
	default:
		break;
	}
	return temp;
}

// returns a vector of the specific objects, which the dynamic object collides with
std::vector<char> DynamicObject::is_on_something(Map& map, sf::Keyboard::Key key)
{
	std::vector<std::shared_ptr<StaticObject>> * static_arr = map.get_static();

	int size = static_arr->size();

	sf::Vector2f location = get_next_location(key);

	sf::Vector2f location_right, location_left;
	location_left = location_right = location;

	std::vector<char> collision;

	for (int i = 0; i < size; i++)
	{
		// coin signal
		if ((*static_arr)[i]->get_name() == COIN && (*static_arr)[i]->in_bounds(location))
			collision.push_back(COIN);

		// pole signal
		location.y += 5;
		if ((*static_arr)[i]->get_name() == POLE && (*static_arr)[i]->in_bounds(location))
			collision.push_back(POLE);
		location.y -= 5;
		
		// ladder signal
		location_left.x += 20;
		if (((*static_arr)[i]->get_name() == LADDER && (*static_arr)[i]->in_bounds(location_left)) ||
			((*static_arr)[i]->get_name() == LADDER && (*static_arr)[i]->in_bounds(location_right)))
			collision.push_back(LADDER);
		location_left.x -= 20;

		// specific case where the playe can stand on the ladder
		location_left.y += 40;
		if (((*static_arr)[i]->get_name() == LADDER && (*static_arr)[i]->in_bounds(location_left)) ||
			((*static_arr)[i]->get_name() == LADDER && (*static_arr)[i]->in_bounds(location_right)))
			collision.push_back(LADDER);
		location_left.y -= 40;

		// wall signal
		location_left.x += 35;
		if (((*static_arr)[i]->get_name() == GROUND && (*static_arr)[i]->in_bounds(location_left)) ||
			((*static_arr)[i]->get_name() == GROUND && (*static_arr)[i]->in_bounds(location_right)))
			collision.push_back(WALL);
		location_left.x -= 35;

		// ground signal
		location.y += 40;
		if ((*static_arr)[i]->get_name() == GROUND && (*static_arr)[i]->in_bounds(location))
			collision.push_back(GROUND);
		location.y -= 40;
	}
	return collision;
}


sf::Sprite DynamicObject::get_sprite()
{
	return m_sprite;
}