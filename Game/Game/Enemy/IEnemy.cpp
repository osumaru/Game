#include "stdafx.h"
#include "IEnemy.h"

IEnemy::IEnemy() :
	m_enemyStateMachine(this),
	m_enemyMove(this),
	m_enemyTurn(this),
	m_enemySearch(this)
{
}

IEnemy::~IEnemy()
{
	Delete(&m_enemyMove);
	Delete(&m_enemyTurn);
	Delete(&m_enemySearch);
}
