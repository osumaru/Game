#include "stdafx.h"
#include "IEnemy.h"

IEnemy::IEnemy() :
	m_enemyStateMachine(this),
	m_enemyTurn(this),
	m_enemySearch(this)
{
}

IEnemy::~IEnemy()
{
}
