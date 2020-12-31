#pragma once
#include "Entity.h"
#include "EnemyController.h"
#include "Macros.h"


class Monster : public Entity
{
public:

	using Entity::Entity;

	EnemyController * get_controller();


private:
	Algorithms m_algorithms;
	IQ m_iq;

};