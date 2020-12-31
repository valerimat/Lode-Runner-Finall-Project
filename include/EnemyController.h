#pragma once

#include "MovementController.h"
#include "Enemy.h"
#include "Algorithms.h"


class EnemyController :public MovementController
{
public:

	Move(enum IQ);

private:
	Enemy * m_eney;

}