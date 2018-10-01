#include "stdafx.h"
#include "PlayerMove.h"
#include "Player.h"
#include "PlayerSate/PlayerState.h"
#include "../Camera/GameCamera.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"


CPlayerMove::CPlayerMove()
{
}


CPlayerMove::~CPlayerMove()
{
}

bool CPlayerMove::Start()
{

	return true;
}

void CPlayerMove::Update()
{
	if (!GetPlayer().GetIsGround() ||
		GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerJump) {
		return;
	}
	m_PlayerMoveSpeed = GetPlayer().GetMoveSpeed();

	if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerAttack)
	{
		m_PlayerMoveSpeed = CVector3::Zero;

	}

	//移動の入力があるかの判定
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		CVector3 moveSpeed;
		//1フレームに進む距離
		moveSpeed.z = Pad().GetLeftStickY() * GameTime().GetDeltaFrameTime() * WALK_SPEED;
		moveSpeed.x = Pad().GetLeftStickX() * GameTime().GetDeltaFrameTime() * WALK_SPEED;
		CMatrix cameraVm = GetGameCamera().GetViewMatrix();
		cameraVm.Inverse();	//カメラのビュー行列の逆行列

		//カメラの前方向
		CVector3 cameraZ;
		cameraZ.x = cameraVm.m[2][0];
		cameraZ.y = 0.0f;
		cameraZ.z = cameraVm.m[2][2];
		cameraZ.Normalize();

		//カメラの横方向
		CVector3 cameraX;
		cameraX.x = cameraVm.m[0][0];
		cameraX.y = 0.0f;
		cameraX.z = cameraVm.m[0][2];
		cameraX.Normalize();


		//キャラクターを移動させる処理
		m_PlayerMoveSpeed.x = cameraX.x * moveSpeed.x + cameraZ.x * moveSpeed.z;
		m_PlayerMoveSpeed.z = cameraX.z * moveSpeed.x + cameraZ.z * moveSpeed.z;


		//ダッシュの処理
		if (Pad().IsPressButton(enButtonRB))
		{

			m_PlayerMoveSpeed.x *= RUN_SPEED;
			m_PlayerMoveSpeed.z *= RUN_SPEED;
		}
		if (Pad().IsTriggerButton(enButtonA))
		{
			m_PlayerMoveSpeed.y += 5.0f;
		}

	}
	
	else
	{
		m_PlayerMoveSpeed = CVector3::Zero;
		/*CVector3 kansei = m_PlayerMoveSpeed;
		kansei *= GameTime().GetDeltaFrameTime();
		m_PlayerMoveSpeed -= kansei;*/
	}

	GetPlayer().SetMoveSpeed(m_PlayerMoveSpeed);

}
