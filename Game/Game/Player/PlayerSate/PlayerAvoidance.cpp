#include "stdafx.h"
#include "PlayerAvoidance.h"
#include "../Player.h"

#include "../../Camera/GameCamera.h"

void CPlayerAvoidance::Init()
{
	Rotation();
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationAvoidance, 0.1f);
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_manipVec = m_pPlayer->GetPosition() - bonePos;
	m_preBonePos = bonePos;
	m_pPlayerGetter->SetIsInvincible(true);
}

void CPlayerAvoidance::Update()
{
	Move();
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		CVector3 position;
		position = m_preBonePos;
		position += m_manipVec;
		m_pPlayerGetter->SetPosition(position);
		m_pPlayerGetter->SetIsInvincible(false);
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationAvoidanceCombine);
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}

void CPlayerAvoidance::Move()
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
	m_pPlayerGetter->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	characon.SetGravity(gravity);
	m_preBonePos = bonePos;
}

void CPlayerAvoidance::Rotation()
{
	//��������������̃X�e�B�b�N���͂�����
	CVector3 stickDir = m_pPlayerGetter->GetStickDir();
	if (stickDir.x == 0.0f && stickDir.z == 0.0f) {
		//���̂܂ܑO�ɉ������
		return;
	}
	//�J�����̃r���[�s��̋t�s����쐬
	CMatrix viewMatrixInv = GetGameCamera().GetViewMatrix();
	viewMatrixInv.Inverse();
	//�J������Ԃ�X������Z�������v�Z
	CVector3 cameraVecX = { viewMatrixInv.m[0][0], 0.0f, viewMatrixInv.m[0][2] };
	cameraVecX.Normalize();
	CVector3 cameraVecZ = { viewMatrixInv.m[2][0], 0.0f, viewMatrixInv.m[2][2] };
	cameraVecZ.Normalize();
	//�v���C���[�̑O�������v�Z
	CMatrix playerWorldMatrix = m_pPlayer->GetSkinmodel().GetWorldMatrix();
	CVector3 playerForward;
	playerForward.x = playerWorldMatrix.m[2][0];
	playerForward.y = playerWorldMatrix.m[2][1];
	playerForward.z = playerWorldMatrix.m[2][2];
	playerForward.Normalize();
	//�J������Ԃł̃X�e�B�b�N���͕������v�Z
	CVector3 cameraStickDir;
	cameraStickDir.x = cameraVecX.x * stickDir.x + cameraVecZ.x * stickDir.z;
	cameraStickDir.z = cameraVecX.z * stickDir.x + cameraVecZ.z * stickDir.z;
	cameraStickDir.Normalize();
	//�X�e�B�b�N�̕����ƃv���C���[�̑O�����ŉ�]�p�x���v�Z
	float angle = cameraStickDir.Dot(playerForward);
	if (angle > 1.0f) {
		angle = 1.0f;
	}
	else if (angle < -1.0f) {
		angle = -1.0f;
	}
	angle = acosf(angle);
	CVector3 Cross = cameraStickDir;
	Cross.Cross(playerForward);
	if (Cross.y > 0.0f) {
		angle *= -1.0f;
	}
	//�v���C���[����]������
	CQuaternion playerRotation = m_pPlayerGetter->GetRotation();
	CQuaternion rotation;
	rotation.SetRotation(CVector3::AxisY, angle);
	playerRotation.Multiply(rotation);
	m_pPlayerGetter->SetRotation(playerRotation);
}
