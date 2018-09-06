#include "stdafx.h"
#include "IEnemy.h"

IEnemy::IEnemy() :
	m_enemyStateMachine(this)
{
}

IEnemy::~IEnemy()
{
}
