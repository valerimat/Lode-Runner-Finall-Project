#pragma once
#include "DynamicObject.h"
#include "Macros.h"

class Enemy : public DynamicObject
{
public:
	//C-tors:
	using DynamicObject::DynamicObject;
	Enemy(char name, sf::Vector2f locaiton, std::shared_ptr<sf::Texture> texture, int smart);
	//Setters:
	virtual void set_smartness(int i);
	void set_path(std::vector<NextStep> steps);

	//Getters:
	IQ get_iq();

	//helpers:
	void move(float dt);
	bool path_is_empty();

private:

	std::vector<NextStep> m_path;
	IQ m_iq;

};