#include "stdafx.h"
#include "IEnemy.h"
#include "../Scene/SceneManager.h"
#include "../Scene/GameScene.h"
#include "../Map/Map.h"

IEnemy::IEnemy() :
	m_enemyStateMachine(this),
	m_enemyTurn(this),
	m_enemySearch(this),
	m_isDamagePossible(std::make_unique<bool[]>(m_maxPlayerHit))
{
}

IEnemy::~IEnemy()
{
}

void IEnemy::BeforeDead()
{
	Delete(&m_enemyTurn);
	Delete(&m_enemySearch);
	m_enemyStateMachine.Release();
}

bool IEnemy::CalucFanShape(float degree, const CVector3& position)
{
	//���[���h�s�񂩂烂�f���̑O�������擾
	CMatrix worldMatrix = GetWorldMatrix();
	CVector3 forwardXZ;
	forwardXZ.x = worldMatrix.m[2][0];
	forwardXZ.y = 0.0f;
	forwardXZ.z = worldMatrix.m[2][2];
	forwardXZ.Normalize();

	CVector3 dir = position - m_position;
	dir.y = 0.0f;
	dir.Normalize();

	float angle = dir.Dot(forwardXZ);
	angle = acosf(angle);

	if (fabsf(angle) < CMath::DegToRad(degree))
	{
		//���͈̔͂ɂ���
		return true;
	}
	return false;
}

void IEnemy::EnemyListErase()
{
	//�G�l�~�[�����S���Ă����烊�X�g����폜
	std::list<IEnemy*>& enemyList = GetSceneManager().GetMap()->GetEnemyList();
	enemyList.erase(m_iterater);
}

void IEnemy::UpdateSpinePos()
{
	m_spinePos.x = m_spineMatrix->m[3][0];
	m_spinePos.y = m_spineMatrix->m[3][1];
	m_spinePos.z = m_spineMatrix->m[3][2];
}