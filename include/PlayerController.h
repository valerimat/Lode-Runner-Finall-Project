#pragma once
#include "MovementController.h"
#include "Player.h"



class PlayerController:public MovementController
{
public:
	Move(int key);

private:
	Player * m_player;

}