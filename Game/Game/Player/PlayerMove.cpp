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
	//プレイヤーの速度を取得
	m_PlayerMoveSpeed = GetPlayer().GetMoveSpeed();

	//ダメージを受けているときは移動しない
	//プレイヤーが空中にいる時も移動させない
	//攻撃中も移動させない
	if (
		GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerDamage ||
		GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerAttack
		)
	{
		
		m_PlayerMoveSpeed.x = 0.0f;
		m_PlayerMoveSpeed.z = 0.0f;
	}

	//回避中の移動処理
	else if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerAvoidance)
	{
		m_PlayerMoveSpeed = {0.0f, 0.0f, 0.0f};
		////プレイヤーのワールド行列の取得
		CMatrix PlayerWorldMatrix = GetPlayer().GetPlayerSkin().GetWorldMatrix();
		////プレイヤーの前方向の取得
		CVector3 PlayerFront = { PlayerWorldMatrix.m[1][0],PlayerWorldMatrix.m[1][1],PlayerWorldMatrix.m[1][2] };
		PlayerFront.Normalize();
		PlayerFront *= 300.0f;
		CVector3 OneVec = CVector3::One;
		if (m_PlayerMoveSpeed.Length() == 0)
		{
			m_PlayerMoveSpeed -= PlayerFront * GameTime().GetDeltaFrameTime();
		}
		else
		{

			m_PlayerMoveSpeed -= m_PlayerMoveSpeed * GameTime().GetDeltaFrameTime();

		}

	}
	else if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerWireMove)
	{

	}
	//移動の入力があるかの判定
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		CVector3 moveSpeed;
		//1フレームに進む距離
		moveSpeed.z = Pad().GetLeftStickY() * WALK_SPEED;
		moveSpeed.x = Pad().GetLeftStickX() * WALK_SPEED;
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
			if (GetPlayer().GetPlayerStateMachine().GetState() != CPlayerState::EnPlayerState::enPlayerRunJump)
			{

				m_PlayerMoveSpeed.y += 5.0f;
			}
		}
	}


		
	//立ちアニメーションの処理
	else
	{
		m_PlayerMoveSpeed.x = 0.0f;
		m_PlayerMoveSpeed.z = 0.0f;
	
	}

	//キャラクターコントローラーのアップデート処理
	{
		GetPlayer().GetCharacterController().SetPosition(GetPlayer().GetPosition());
		GetPlayer().GetCharacterController().SetMoveSpeed(m_PlayerMoveSpeed);
		GetPlayer().GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

		GetPlayer().SetPosition(GetPlayer().GetCharacterController().GetPosition());
		GetPlayer().SetMoveSpeed(GetPlayer().GetCharacterController().GetMoveSpeed());
	}
}
