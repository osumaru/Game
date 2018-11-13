#include "stdafx.h"
#include "PlayerAvoidance.h"
#include "../Player.h"



void CPlayerAvoidance::Init()
{
	m_pPlayer->PlayAnimation(enPlayerAnimationAvoidance, 0.1f);
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetPlayerSkin().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_manipVec = m_pPlayer->GetPosition() - bonePos;
	m_preBonePos = bonePos;
	m_pPlayer->SetInterval(true);
}

void CPlayerAvoidance::Update()
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
	CCharacterController& characon = m_pPlayer->GetCharacterController();
	float gravity = characon.GetGravity();
	characon.SetGravity(-0.1f);
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
		//CVector3 playerFront;
		//playerFront.x = m_pPlayer->GetWorldMatrix().m[2][0];
		//playerFront.y = m_pPlayer->GetWorldMatrix().m[2][1];
		//playerFront.z = m_pPlayer->GetWorldMatrix().m[2][2];
		//if (playerFront.Dot(movePos) < 0.0f)
		//{
			playerPos += movePos;
		//}
	}
	playerPos.y = characon.GetPosition().y;
	m_pPlayer->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	characon.SetGravity(gravity);
	m_preBonePos = bonePos;
	if (!GetPlayer().GetAnimation().IsPlay())
	{
		CVector3 position;
		position = bonePos;
		position += m_manipVec;
		m_pPlayer->SetPosition(position);

		m_pPlayer->SetInterval(false);
		GetPlayer().PlayAnimation(enPlayerAnimationAvoidanceCombine);
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}
