#include "stdafx.h"
#include "PlayerAvoidance.h"
#include "../Player.h"

#include "../../Camera/GameCamera.h"

void CPlayerAvoidance::Init()
{
	const float RollVolume = 0.3f;
	CSoundSource* RollSound = New<CSoundSource>(0);
	RollSound->Init("Assets/sound/Battle/Roll.wav");
	RollSound->Play(false);
	RollSound->SetVolume(RollVolume);
	Rotation();
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationAvoidance, 0.1f);
	m_pPlayerGetter->GetAnimation().Update(0.0f);
	m_pPlayerGetter->SkinModelUpdate();
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_pPlayerGetter->SetIsInvincible(true);
}

void CPlayerAvoidance::Update()
{
	Move();
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		CVector3 bonePos;
		bonePos.x = m_pBoneMat->m[3][0];
		bonePos.y = m_pBoneMat->m[3][1];
		bonePos.z = m_pBoneMat->m[3][2];
		CVector3 position;
		position = bonePos;
		position.y = m_pPlayer->GetPosition().y;
		m_pPlayerGetter->SetPosition(position);
		m_pPlayerGetter->SetCharaconPos(position);
		m_pPlayerGetter->SetIsInvincible(false);
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationAvoidanceCombine);
		m_pPlayerGetter->GetAnimation().Update(GameTime().GetDeltaFrameTime());
		m_pPlayerGetter->SkinModelUpdate();
		if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAvoidance))
		{
			CVector3 stickDir = CVector3::Zero;
			stickDir.x = Pad().GetLeftStickX();
			stickDir.z = Pad().GetLeftStickY();
			stickDir.Normalize();
			m_pPlayerGetter->SetStickDir(stickDir);
			Init();
		}
		else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
		{
			GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
		}
		else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStand))
		{
			GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
		}
	}

}

void CPlayerAvoidance::Move()
{
	CVector3 playerPos = m_pPlayer->GetPosition();
	CVector3 bonePos;
	bonePos.x = m_pBoneMat->m[3][0];
	bonePos.y = m_pBoneMat->m[3][1];
	bonePos.z = m_pBoneMat->m[3][2];
	

	CCharacterController& characon = m_pPlayerGetter->GetCharacterController();
	//���̂̍��W��ۑ�
	CVector3 rigidPos = characon.GetPosition();
	bonePos.y = characon.GetPosition().y;
	characon.SetPosition(bonePos);
	//�v���C���[�̂̃{�[�����W����v���C���[�̍��W�܂ł̃x�N�g�����쐬
	CVector3 boneDistance = playerPos - bonePos;
	characon.DynamicExecute();
	characon.SetMoveSpeed({ 0.0f, m_fallSpeed, 0.0f });
	characon.Execute(GameTime().GetDeltaFrameTime());
	
	rigidPos = characon.GetPosition();
	//�Փˉ����������W�ɂ������쐬�����x�N�g���𑫂�
	playerPos = rigidPos + boneDistance;
	//�������x�����ۑ�
	m_fallSpeed = characon.GetMoveSpeed().y;
	//�v���C���[�ƍ��̂̍��W���X�V
	m_pPlayerGetter->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	//���̂̍��W��߂�
	characon.SetPosition(rigidPos);
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
