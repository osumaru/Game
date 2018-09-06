#include "stdafx.h"
#include "Player.h"
#include "../GameCamera.h"

void CPlayer::Init(CVector3 position)
{
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_Weaponskin.Load(L"Assets/modelData/Sword.cmo", NULL);
	m_position = position;
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);
	m_characterController.Init(3.5f, 0.05f,{m_position.x,m_position.y, m_position.z });
	m_characterController.SetGravity(-9.8f);
	wchar_t* animClip[5] = {{ L"Assets/modelData/PlayerStand.tka"},			//待機アニメーション	
							{ L"Assets/modelData/PlayerDashStay.tka" },		//歩行アニメーション
							{ L"Assets/modelData/PlayerJump.tka" },			//ジャンプアニメーション
							{ L"Assets/modelData/PlayerAttack.tka" },		//攻撃アニメーション
							{ L"Assets/modelData/PlayerDamage.tka" } };		//ダメージアニメーション
	m_animation.Init(animClip, 5);
	m_animation.SetLoopFlg(0, true);
	m_animation.SetLoopFlg(1, false);

	//プレイヤーのステータスの初期化
	{

		m_status.Strength	= 10;						//攻撃力
		m_status.Defense	= 3;						//防御力
		m_status.Health		= 100;						//体力
		m_status.Level		= 1;						//レベル
		m_status.OldExp		= 15;						//ひとつ前のレベルに必要な経験値
		m_status.NextExp	= ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12 )) / 2 + 0.5;		//次のレベルアップに必要な経験値
		m_status.ExperiencePoint = 0;					//経験値
		m_status.AccumulationExp += m_status.OldExp;	//累積経験値
	}

	Add(this, 0);
}

void CPlayer::Update()
{

	

	AnimationMove();		//アニメーションの処理
	Move();					//移動処理
	Rotation();				//回転処理
	StatusCalculation();	//ステータスの処理

	if (Pad().IsTriggerButton(enButtonB))
	{
		m_status.ExperiencePoint += 43;
		m_status.AccumulationExp += 43;
		
	}
	//スキンモデルの更新
	m_skinmodel.Update(m_position, m_rotation, { 3.0f, 3.0f, 3.0f }, true);
	//プレイヤーの手のボーンを取得
	CMatrix PlayerHnd = m_skinmodel.FindBoneWorldMatrix(L"LeftHandMiddle1");
	CVector3 PlayerHndPos = { PlayerHnd.m[3][0],PlayerHnd.m[3][1],PlayerHnd.m[3][2] };
	
	m_WeaponPosition = PlayerHndPos;
	m_Weaponrotation.SetRotation(PlayerHnd);
	CQuaternion Xrot = CQuaternion::Identity;
	Xrot.SetRotationDeg(CVector3::AxisX, 90.0f);

	m_Weaponskin.Update(m_WeaponPosition, m_Weaponrotation, { 3.0f, 3.0f, 3.0f }, true);
	
}

void CPlayer::Draw()
{
	m_characterController.Draw();
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	m_Weaponskin.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	
}

void CPlayer::Move()
{
	if (m_characterController.IsOnGround())
	{

		m_moveSpeed = { 0.0f,0.0f,0.0f };

	}
	else
	{

		m_moveSpeed = m_characterController.GetMoveSpeed();

	}
	//

		CVector3 moveSpeed;
		moveSpeed.z = Pad().GetLeftStickY() * GameTime().GetDeltaFrameTime() * 2500;
		moveSpeed.x = Pad().GetLeftStickX() * GameTime().GetDeltaFrameTime() * 2500;

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
		m_moveSpeed.x = cameraX.x * moveSpeed.x + cameraZ.x * moveSpeed.z;
		//m_moveSpeed.y = 0;
		m_moveSpeed.z = cameraX.z * moveSpeed.x + cameraZ.z * moveSpeed.z;


	//ダッシュの処理
	if (Pad().IsPressButton(enButtonRB))
	{
		
		m_moveSpeed.x *= 5.0f;
		m_moveSpeed.z *= 5.0f;
	}

	else if (Pad().IsTriggerButton(enButtonY))
	{

		//m_moveSpeed.y += 50.0f;
	}
	

	//回避の処理
	if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		m_isSlip = true;
	}

	if(m_isSlip)
	{
		//m_slipSpeed = m_slipSpeed - (60.0f * GameTime().GetDeltaFrameTime());
		//if (m_slipSpeed <= 0)
		//{
		//	m_isSlip = false;
		//	m_slipSpeed = 50.0f;
		//	return;
		//}
		//CVector3 playerFlontVec = { m_skinmodel.GetWorldMatrix().m[2][0],0.0f,m_skinmodel.GetWorldMatrix().m[2][2] };
		//playerFlontVec.Normalize();
		//m_moveSpeed = playerFlontVec * m_slipSpeed;
	}

	m_characterController.SetMoveSpeed(m_moveSpeed);
	

	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();
}

//プレイヤーの回転を行う関数
void CPlayer::Rotation()
{

	CVector3 playerVec = m_moveSpeed; //
	playerVec.y = 0.0f;


	if (playerVec.LengthSq() > 0.001f)
	{


		CQuaternion rot = CQuaternion::Identity;
		rot.SetRotation(CVector3::AxisY, atan2f(playerVec.x, playerVec.z));		//Y軸周りの回転
		m_rotation.Slerp(0.2f, m_rotation, rot);


	}

}

void CPlayer::AnimationMove()
{
	//攻撃アニメーションの処理
	if (Pad().IsTriggerButton(enButtonX) && m_animation.GetCurrentAnimationNum() != 3)
	{
		m_animation.Play(3, 0.1f);
	}

	//ジャンプアニメーションの処理
	else if (Pad().IsTriggerButton(enButtonY))
	{
		m_animation.Play(2, 0.5);

	}

	//歩行アニメーションの処理
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0 )
	{
		m_animation.SetLoopFlg(1, true);
		if (m_animation.GetCurrentAnimationNum() != 1)
		{

			m_animation.Play(1, 0.2);
		}
	}
	
	//待機モーション
	if (m_animation.GetCurrentAnimationNum() != 0 && Pad().GetLeftStickX() == 0 && Pad().GetLeftStickY() == 0)
	{
		m_animation.SetLoopFlg(1, false);
		if (!m_animation.IsPlay() || m_animation.GetCurrentAnimationNum() == 1)
		{

			m_animation.Play(0, 0.2f);

		}

	}

	m_animation.Update(GameTime().GetDeltaFrameTime());

}

void CPlayer::StatusCalculation()
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

void  CPlayer::WeaponChange()
{



}