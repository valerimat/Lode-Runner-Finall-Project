#pragma once
#include "Entity.h"
#include "Lives.h"
#include "PlayerController.h"

class Player : public Entity
{
public:

	using Entity::Entity();

	Lives* get_lives();

	PlayerController * get_controller();
	

private:
	Lives m_lives;



};