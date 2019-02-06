#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//�ړ����Ȃ�
	CVector3 moveSpeed = CVector3::Zero;
	m_enemy->SetMoveSpeed(moveSpeed);
	//�G�l�~�[���U������
	m_enemy->Attack();
	
	//�U����
	const float AttackVolume = 0.3f;
	CSoundSource* AttackSound = New<CSoundSource>(0);
	AttackSound->Init("Assets/sound/Battle/WarrokEnemyAttackSE.wav");
	AttackSound->Play(false);
	AttackSound->SetVolume(AttackVolume);
	return true;
}

void CEnemyAttack::Update()
{
	if (m_enemy->GetIsDamage()) {
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage); 
	}
	if (!m_enemy->GetAnimation().IsPlay()) {
		//�A�j���[�V�������I�����Ă���
		m_esm->ChangeState(CEnemyState::enState_AttackWait);
	}
}