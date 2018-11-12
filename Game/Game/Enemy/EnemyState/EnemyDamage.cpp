#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../EnemyGroup.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"
#include "../../UI/DamageNumber/DamageNumber.h"

CEnemyDamage::~CEnemyDamage()
{
	Delete(m_damageNumber);
}

bool CEnemyDamage::Start()
{
	//�_���[�W�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	m_damageNumber = New<CDamageNumber>(0);
	m_damageNumber->Init();

	//�_���[�W�v�Z
	int playerStrength = GetPlayer().GetStatus().Strength;
	int enemyDefence = m_enemy->GetStatus().Defense;
	int damage = playerStrength - enemyDefence;
	m_enemy->HpDamage(damage);
	m_damageNumber->DamageCalculation(damage);

	CMatrix leftShoulderMatrix = m_enemy->GetBoneWorldMatrix(L"LeftShoulder");
	m_damagePos.x = leftShoulderMatrix.m[3][0];
	m_damagePos.y = leftShoulderMatrix.m[3][1];
	m_damagePos.z = leftShoulderMatrix.m[3][2];

	return true;
}

void CEnemyDamage::Update()
{
	CMatrix viewMatrix = GetGameCamera().GetViewMatrix();
	CMatrix projectionMatrix = GetGameCamera().GetProjectionMatrix();
	//�r���[�ϊ�
	CVector4 viewPosition = m_damagePos;
	viewMatrix.Mul(viewPosition);
	//�v���W�F�N�V�����ϊ�
	CVector4 projectionPosition = viewPosition;
	projectionMatrix.Mul(projectionPosition);
	projectionPosition = projectionPosition / projectionPosition.w;
	//�X�N���[���ϊ�
	CVector2 screenPosition;
	screenPosition.x = (1.0f + projectionPosition.x) / 2.0f * FrameBufferWidth() - (FrameBufferWidth() / 2.0f);
	screenPosition.y = (1.0f + projectionPosition.y) / 2.0f * FrameBufferHeight() - (FrameBufferHeight() / 2.0f);
	m_damageNumber->SetPosition(screenPosition);

	//�v���C���[�Ƃ̋������v�Z����
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();
	//���͈̔͂ɂ��邩�ǂ�������
	bool isRange = m_enemy->CalucFanShape(20.0f, playerPos);

	if (!m_enemy->IsPlayAnimation()) {
		//�A�j���[�V�������I�����Ă���
		if (isRange  && length < 2.0f) {
			//�߂���΍U��
			m_esm->ChangeState(CEnemyState::enState_Attack);
		}
		else if (m_enemy->IsFind()) {
			//��������Ă�����v���C���[��ǂ�������
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
		//�_���[�W���󂯂��t���O��߂�
		m_enemy->SetIsDamage(false);
	}
	if (m_enemy->GetStatus().Hp <= 0) {
		//HP�������Ȃ�Ύ��S
		m_esm->ChangeState(CEnemyState::enState_Death);
		//�_���[�W���󂯂��t���O��߂�
		m_enemy->SetIsDamage(false);
	}
}
