#pragma once
#include "DynamicObject.h"
#include "Macros.h"


class Enemy : public DynamicObject
{
public:
	using DynamicObject::DynamicObject;
	IQ get_iq();
	virtual void set_smartness();
	void set_path(std::vector<NextStep> steps);
	void move();
	
private:
	std::vector<NextStep> m_path;
	IQ m_iq;

};