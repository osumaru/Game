#include "stdafx.h"
#include "Player.h"
#include "../GameCamera.h"

void Player::Init(Vector3 position)
{
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_position = position;
	m_characterController.Init(2.0f, 2.0f, m_position);
	m_characterController.SetGravity(-9.0f);
	wchar_t* animClip[2] = { L"Assets/modelData/unity2.tka", L"Assets/modelData/unity3.tka" };
	m_animation.Init(animClip, 2);

	//プレイヤーのステータスの初期化
	{

		m_status.Strength	= 10;				//攻撃力
		m_status.Defense	= 3;				//防御力
		m_status.Health		= 100;				//体力
		m_status.Level		= 1;				//レベル
		m_status.OldExp		= 15;				//ひとつ前のレベルに必要な経験値
		m_status.NextExp	= ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12 )) / 2 + 0.5;		//次のレベルアップに必要な経験値
		m_status.ExperiencePoint = 0;				//経験値
		m_status.AccumulationExp += m_status.OldExp;	//累積経験値
	}

	Add(this, 0);
}

void Player::Update()
{

	Move();					//移動処理
	Rotation();				//回転処理
	//AnimationMove();		//アニメーションの処理
	StatusCalculation();	//ステータスの処理

	if (GetPad().IsTriggerButton(enButtonB))
	{
		m_status.ExperiencePoint += 43;
		m_status.AccumulationExp += 43;

	}

	//スキンモデルの更新
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);


}

void Player::Draw()
{
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void Player::Move()
{
	

		Vector3 moveSpeed;
		moveSpeed.z = GetPad().GetLeftStickY() * GetGameTime().GetDeltaFrameTime() * 5;
		moveSpeed.x = GetPad().GetLeftStickX() * GetGameTime().GetDeltaFrameTime() * 5;

		Matrix cameraVm = GetGameCamera().GetViewMatrix();
		cameraVm.Inverse();	//カメラのビュー行列の逆行列

		//カメラの前方向
		Vector3 cameraZ;
		cameraZ.x = cameraVm.m[2][0];
		cameraZ.y = 0.0f;
		cameraZ.z = cameraVm.m[2][2];
		cameraZ.Normalize();

		//カメラの横方向
		Vector3 cameraX;
		cameraX.x = cameraVm.m[0][0];
		cameraX.y = 0.0f;
		cameraX.z = cameraVm.m[0][2];
		cameraX.Normalize();

		//キャラクターを移動させる処理
		m_moveSpeed.x = cameraX.x * moveSpeed.x + cameraZ.x * moveSpeed.z;
		m_moveSpeed.z = cameraX.z * moveSpeed.x + cameraZ.z * moveSpeed.z;

		if (GetPad().IsPressButton(enButtonRB))
		{
			m_moveSpeed *= 5;

		}

		m_characterController.SetMoveSpeed(m_moveSpeed);
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GetGameTime().GetDeltaFrameTime());

		m_position = m_characterController.GetPosition();

}

void Player::Rotation()
{

	Vector3 playerVec = m_moveSpeed;


	if (playerVec.LengthSq() > 0.001f)
	{


		Quaternion rot = Quaternion::Identity;
		rot.SetRotation(Vector3::AxisY, atan2f(playerVec.x, playerVec.z));		//Y軸周りの回転
		m_rotation.Slerp(0.02f, m_rotation, rot);


	}

}

void Player::AnimationMove()
{

	if (GetPad().IsTriggerButton(enButtonA))
	{
		m_animation.Play(0);
	}

	m_animation.Update(GetGameTime().GetDeltaFrameTime());

}

void Player::StatusCalculation()
{
	//レベルアップの処理
	if (m_status.NextExp <= m_status.ExperiencePoint)
	{
		m_status.ExperiencePoint -= m_status.NextExp;

		m_status.Level += 1;

		m_status.OldExp = m_status.NextExp;

		m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5;		//次のレベルアップに必要な経験値

		//10レベルごとのステータスの上昇量
		if (m_status.Level % 10 == 0)
		{

			m_status.Strength	+= 9;
			m_status.Defense	+= 6;
			m_status.Health		+= 25;


		}
		//偶数レベルごとのステータスの上昇量
		else if (m_status.Level % 2 == 0)
		{

			m_status.Strength += 5;
			m_status.Defense += 3;
			m_status.Health += 14;

		}

		else
		{
			m_status.Strength += 2;
			m_status.Defense += 2;
			m_status.Health += 11;
		}

	}


}