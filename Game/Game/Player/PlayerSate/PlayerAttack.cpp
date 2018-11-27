#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"
#include "../../Scene/GameScene.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"
#include "../../Scene/SceneManager.h"
#include "../../Enemy/Maw.h"


CPlayerAttack::CPlayerAttack()
{
	m_attackAnimation[0] = enPlayerAnimationAttack1;
	m_attackAnimation[1] = enPlayerAnimationAttack2;
	m_attackAnimation[2] = enPlayerAnimationAttack3;
	m_combineAnimation[0] = enPlayerAnimationAttackCombine1;
	m_combineAnimation[1] = enPlayerAnimationAttackCombine2;
	m_combineAnimation[2] = enPlayerAnimationAttackCombine3;
}

void CPlayerAttack::Init()
{

	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_attackCount = 0;
	m_isContinuationAttack = false;
	m_pPlayerGetter->GetAnimation().Play(m_attackAnimation[m_attackCount], 0.2f);	
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_manipVec = m_pPlayer->GetPosition() - bonePos;
	m_preBonePos = bonePos;
	m_pPlayer->GetWeaponManager().SetIsAttack(true);
	m_pPlayer->GetWeaponManager().WeaponTraceDrawReset();
	m_isPreDodge = false;
}

void CPlayerAttack::Update()
{
	//�U�����ɍU���̓��͂����ꂽ�ꍇ�͘A���Ɉڍs����
	if (Pad().IsTriggerButton(enButtonRightTrigger) && !m_isContinuationAttack && m_attackCount < MAX_ATTACK_NUM - 1)
	{
		m_isContinuationAttack = true;
		m_attackCount++;
	}

	Move();
	m_pPlayer->GetWeaponManager().GetWeapon(m_pPlayer->GetWeaponManager().GetCurrentState())->EnemyAttack();

	if (Pad().IsTriggerButton(enButtonB)) {
		m_isPreDodge = true;
	}

	//�U���A�j���[�V�������I��������̏���
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		//�G�l�~�[�̃��X�g���擾
		for (const auto& enemys : GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
		{
			enemys->SetIsDamagePossible(true);
		}
		//�U�����[�V�������̓_���[�W���[�V�����������Ȃ�
		if (m_isContinuationAttack)
		{
			m_isContinuationAttack = false;
			m_pPlayerGetter->GetAnimation().Play(m_attackAnimation[m_attackCount], 0.2f);
			m_pPlayer->GetWeaponManager().WeaponTraceDrawReset();
		}
		else
		{
			m_pPlayer->GetWeaponManager().SetIsAttack(false);
			CVector3 position;
			position = m_preBonePos;
			position += m_manipVec;
			position.y = m_pPlayerGetter->GetCharacterController().GetPosition().y;
			m_pPlayerGetter->SetPosition(position);

			m_pPlayerGetter->GetAnimation().Play(m_combineAnimation[m_attackCount]);
			if (m_isPreDodge)
			{
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
			}
			else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
			{
				//����A�j���[�V����
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
			}
			else
			{
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);

			}
		}
	}
}

void CPlayerAttack::Move()
{
	//�v���C���[�̑O�̃t���[���̃{�[���̍��W���獡�̃{�[���̍��W�����C�e�X�g���Ă߂荞��ł���Ή����߂�
	CVector3 playerPos = m_pPlayer->GetPosition();
	CVector3 bonePos;
	bonePos.x = m_pBoneMat->m[3][0];
	bonePos.y = m_pBoneMat->m[3][1];
	bonePos.z = m_pBoneMat->m[3][2];

	//�O�̃t���[���Ƃ̍��W�ƍ��̍��W�������Ĉړ��ʂ��v�Z
	CVector3 moveSpeed = bonePos - m_preBonePos;
	moveSpeed.y = 0.0f;
	CCharacterController& characon = m_pPlayerGetter->GetCharacterController();
	float gravity = characon.GetGravity();
	characon.SetGravity(-0.3f);
	//�������v���C���\�̍��W�ł��낦��
	m_preBonePos.y = playerPos.y;
	characon.SetMoveSpeed(moveSpeed);
	characon.SetPosition(m_preBonePos);
	characon.Execute(1.0f);
	//�����ɓ������Ă���΃v���C���[�̍��W�𓮂����ăA�j���[�V�����̈ړ��ʂ�ł�����
	if (characon.GetWallCollisionObject() != nullptr)
	{
		CVector3 movePos = characon.GetPosition() - bonePos;
		movePos.y = 0.0f;
		CVector3 playerFront;
		playerFront.x = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][0];
		playerFront.y = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][1];
		playerFront.z = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][2];
		if (playerFront.Dot(movePos) < 0.0f)
		{
			playerPos += movePos;
		}
	}
	playerPos.y = characon.GetPosition().y;
	m_pPlayerGetter->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	characon.SetGravity(gravity);
	m_preBonePos = bonePos;
}

