#include "stdafx.h"
#include "EnemyChase.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../PathFinding/PathFinding.h"

bool CEnemyChase::Start()
{
	//�����A�j���[�V�������Đ�
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Chase, 0.3f);

	return true;
}

void CEnemyChase::Update()
{
	//�v���C���[�Ƃ̋������v�Z
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerDir = playerPos - m_enemy->GetPosition();
	toPlayerDir.y = 0.0f;
	float length = toPlayerDir.Length();

	if (m_enemy->GetAttackType() == IEnemy::enAttackType_Far) {
		//�������U�����ł���^�C�v������
		if (length < 4.0f)
		{
			//�ߋ����U��������
			m_enemy->SetAttackLength(1.2f);
		}
		else
		{
			//�������U��������
			m_enemy->SetAttackLength(10.0f);
		}
	}

	Move(length);

	//�U���͈͂ɂ��邩
	bool isRange = m_enemy->CalucFanShape(10.0f, playerPos);

	if (m_enemy->GetIsDamage()){
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (isRange && length < m_enemy->GetAttackLength()) {
		//�U���͈͂ɓ����Ă���
		m_esm->ChangeState(CEnemyState::enState_Attack);
	}
	if (!m_enemy->IsFind()) {
		//�v���C���[�����ꂽ��߂��Ă���
		m_esm->ChangeState(CEnemyState::enState_Idle);
	}
}

void CEnemyChase::Move(float length)
{
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	float speed = 3.0f;
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 enemyPos = m_enemy->GetPosition();
	CVector3 toPlayerDir = playerPos - enemyPos;
	if (length > 3.0f) 
	{
		//�o�H�T������
		m_interval++;
		if (m_interval % 5 == 0) {
			CVector3 startPos = enemyPos;
			CVector3 targetPos = playerPos;
			g_pathFinding.FindRoot(m_root, startPos, targetPos);

			if (m_root.empty()) {
				return;
			}
			CVector3 rootPos;
			m_iterater = m_root.begin();
			while(m_iterater != m_root.end()) {
				m_iterater->CopyTo(rootPos);
				CVector3 rootDir = rootPos - m_root[0];
				if (rootDir.LengthSq() < FLT_EPSILON)
				{
					m_iterater++;
				}
				else 
				{
					break;
				}
			}
			CVector3 pos = enemyPos;
			pos.y = 0.0f;
			rootPos -= pos;
			rootPos.Normalize();
			moveSpeed.x = rootPos.x * 5.0f;
			moveSpeed.z = rootPos.z * 5.0f;
		}
	}
	else {
		//�v���C���[��ǂ�������
		toPlayerDir.Normalize();
		toPlayerDir *= speed;
		moveSpeed.x = toPlayerDir.x;
		moveSpeed.z = toPlayerDir.z;
	}
	m_enemy->SetMoveSpeed(moveSpeed);
}
