#include "stdafx.h"
#include "PlayerRotation.h"
#include "Player.h"
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"


CPlayerRotation::CPlayerRotation()
{
}


CPlayerRotation::~CPlayerRotation()
{
}

bool CPlayerRotation::Start()
{
	return true;
}

void CPlayerRotation::Update()
{
	CVector3 playerVec = GetPlayer().GetMoveSpeed();
	playerVec.y = 0.0f;
	//�v���C���[�̃��[���h�s��̎擾
	CMatrix PlayerWorldMatrix = GetPlayer().GetPlayerSkin().GetWorldMatrix();
	//����̍��W�Ɖ�]�̏�����
	CVector3		weaponPosition = GetPlayer().GetWeaponPosition();
	CQuaternion		weaponRot;
	//�v���C���[�̑O�����̎擾
	CVector3 PlayerFront = { PlayerWorldMatrix.m[1][0],PlayerWorldMatrix.m[1][1],PlayerWorldMatrix.m[1][2] };
	PlayerFront.Normalize();


	//�v���C���[�̔w���ɕ�������������邽�߂̏���
	if (!GetPlayer().GetIsAttack())
	{
		//�v���C���[�̃{�[���̏����擾
		CMatrix PlayerSpine = GetPlayer().GetPlayerSkin().FindBoneWorldMatrix(L"Spine2");
		CVector3 PlayerSpinePos = { PlayerSpine.m[3][0],PlayerSpine.m[3][1],PlayerSpine.m[3][2] };
		CVector3 PlayerHndScale = { PlayerSpine.m[0][0], PlayerSpine.m[0][1], PlayerSpine.m[0][2] };
		float len = PlayerHndScale.Length();
		PlayerSpine.m[0][0] /= len;
		PlayerSpine.m[0][1] /= len;
		PlayerSpine.m[0][2] /= len;

		PlayerSpine.m[1][0] /= len;
		PlayerSpine.m[1][1] /= len;
		PlayerSpine.m[1][2] /= len;

		PlayerSpine.m[2][0] /= len;
		PlayerSpine.m[2][1] /= len;
		PlayerSpine.m[2][2] /= len;
		GetPlayer().SetWeaponPosition(PlayerSpinePos);

		//�ړ����̕���̍��W�̐ݒ�
		if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerWalk ||
			GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerRun)
		{
			PlayerFront *= 0.0f;
			weaponPosition = GetPlayer().GetPosition();
			weaponPosition.y = PlayerSpinePos.y;
			weaponPosition.Add(PlayerFront);
			GetPlayer().SetWeaponPosition(weaponPosition);

		}
		//�W�����v���̕���̈ʒu
		if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerJump)
		{
			PlayerFront *= 0.0f;
			weaponPosition = GetPlayer().GetPosition();
			weaponPosition.y = PlayerSpinePos.y;
			weaponPosition.Add(PlayerFront);
			GetPlayer().SetWeaponPosition(weaponPosition);
		}

		//�ړ����ȊO�̕���̍��W�̐ݒ�
		else
		{

			PlayerFront *= 0.16f;
			weaponPosition = GetPlayer().GetPosition();
			weaponPosition.y = PlayerSpinePos.y;
			weaponPosition.Add(PlayerFront);
			GetPlayer().SetWeaponPosition(weaponPosition);
		}

		//����̉�]���s������
		{
			weaponRot.SetRotation(PlayerSpine);
			CQuaternion rotX, rotY ,rotZ;
			rotX.SetRotationDeg(CVector3::AxisX, 180.0f);
			rotY.SetRotationDeg(CVector3::AxisY, 90.0f);
			rotZ.SetRotationDeg(CVector3::AxisZ, 90.0f);
			weaponRot.Multiply(rotX);
			weaponRot.Multiply(rotY);
			GetPlayer().SetWeaponRotation(weaponRot);
		}
	}
	//�v���C���[�̎�̃{�[���ɕ�����������鏈��
	else 
	{
		//�v���C���[�̎�̃{�[�����擾
		CMatrix PlayerHnd = GetPlayer().GetPlayerSkin().FindBoneWorldMatrix(L"LeftHandMiddle1");
		CVector3 PlayerHndPos = { PlayerHnd.m[3][0],PlayerHnd.m[3][1],PlayerHnd.m[3][2] };

		CVector3 PlayerHndScale = { PlayerHnd.m[0][0], PlayerHnd.m[0][1], PlayerHnd.m[0][2] };
		float len = PlayerHndScale.Length();
		PlayerHnd.m[0][0] /= len;
		PlayerHnd.m[0][1] /= len;
		PlayerHnd.m[0][2] /= len;

		PlayerHnd.m[1][0] /= len;
		PlayerHnd.m[1][1] /= len;
		PlayerHnd.m[1][2] /= len;

		PlayerHnd.m[2][0] /= len;
		PlayerHnd.m[2][1] /= len;
		PlayerHnd.m[2][2] /= len;
		weaponPosition = PlayerHndPos;
		weaponRot.SetRotation(PlayerHnd);
		CQuaternion multi;
		multi.SetRotationDeg(CVector3::AxisY, 45.0f);
		multi.SetRotationDeg(CVector3::AxisX, 90.0f);
		weaponRot.Multiply(multi);
		GetPlayer().SetWeaponPosition(weaponPosition);
		GetPlayer().SetWeaponRotation(weaponRot);

	}

	//�v���C���[�̉�]�̏���
	if (playerVec.LengthSq() > 0.001f)
	{

		CQuaternion Playerrot = GetPlayer().GetPlayerrRot();
		CQuaternion rot = CQuaternion::Identity;
		rot.SetRotation(CVector3::AxisY, atan2f(playerVec.x, playerVec.z));		//Y������̉�]
		Playerrot.Slerp(0.2f, Playerrot, rot);
		GetPlayer().SetPlayerRot(Playerrot);


	}
}
