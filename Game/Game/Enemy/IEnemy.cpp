#include "stdafx.h"
#include "IEnemy.h"
#include "../Scene/SceneManager.h"
#include "../Scene/GameScene.h"
#include "../Map/Map.h"
#include "EnemyGroup.h"

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

void IEnemy::Init(const SMapChipInfo & info, CAnimation * anim)
{
	MapChip::Init(info, &m_animation);
	Init(info.m_level);
	AddObject();
}

bool IEnemy::Start()
{
	//所属するグループを決める
	CEnemyGroup* group = nullptr;
	std::list<CEnemyGroup*>& enemyGroupList = GetSceneManager().GetMap()->GetEnemyGroupList();
	for (CEnemyGroup* enemyGroup : enemyGroupList)
	{
		if (group == nullptr)
		{
			group = enemyGroup;
			continue;
		}
		CVector3 distance = group->GetPosition();
		distance -= m_position;
		CVector3 distance2 = enemyGroup->GetPosition();
		distance2 -= m_position;
		if (distance2.Length() <= distance.Length())
		{
			group = enemyGroup;
		}
	}
	SetEnemyGroup(group);
	return true;
}

void IEnemy::BeforeDead()
{
	Delete(&m_enemyTurn);
	Delete(&m_enemySearch);
	m_enemyStateMachine.Release();
}

bool IEnemy::CalucFanShape(float degree, const CVector3& position)
{
	//ワールド行列からモデルの前方向を取得
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
		//扇状の範囲にいる
		return true;
	}
	return false;
}

void IEnemy::EnemyListErase()
{
	MapChipDelete();
	m_enemyGroup->EnemyNumReduce();
}

void IEnemy::SetEnemyGroup(CEnemyGroup * enemyGroup)
{
	m_enemyGroup = enemyGroup;
	m_enemyGroup->Add(m_initializeInfo);
}
