#include "stdafx.h"
#include "Player.h"
#include "../GameCamera.h"
#include "../Map/Map.h"

void CPlayer::Init(CVector3 position)
{
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_Weaponskin.Load(L"Assets/modelData/Sword.cmo", NULL);
	m_position = position;
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);
	m_characterController.Init(0.6f, 4.0f,m_position);
	m_characterController.SetGravity(-9.8f);
	wchar_t* animClip[enPlayerNum] = {	{ L"Assets/modelData/PlayerStand.tka"},			//待機アニメーション	
										{ L"Assets/modelData/PlayerWalkStay.tka" },		//歩行アニメーション
										{ L"Assets/modelData/PlayerDashStay.tka" },		//歩行アニメーション
										{ L"Assets/modelData/PlayerJump.tka" },			//ジャンプアニメーション
										{ L"Assets/modelData/PlayerAttack.tka" },		//攻撃アニメーション
										{ L"Assets/modelData/PlayerDamage.tka" },		//ダメージアニメーション
										{  L"Assets/modelData/PlayerKaihi.tka" }
									 };
	m_animation.Init(animClip, enPlayerNum);
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
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
	m_Weaponskin.Update(m_WeaponPosition, m_WeaponRotation, { 1.0f, 1.0f, 1.0f }, true);
	
}

//描画処理
void CPlayer::Draw()
{
	//m_characterController.Draw();
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	if (m_animation.GetCurrentAnimationNum() == enPlayerAtack)
	{

		m_Weaponskin.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());

	}
	
}

void CPlayer::Move()
{
		m_moveSpeed = m_characterController.GetMoveSpeed();

		//移動しているかの判定
		if (m_State != enPlayerStand)
		{


			CVector3 moveSpeed;
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
			m_moveSpeed.x = cameraX.x * moveSpeed.x + cameraZ.x * moveSpeed.z;
			//m_moveSpeed.y = 0;
			m_moveSpeed.z = cameraX.z * moveSpeed.x + cameraZ.z * moveSpeed.z;


			//ダッシュの処理
			if (Pad().IsPressButton(enButtonRB))
			{

				m_moveSpeed.x *= RUN_SPEED;
				m_moveSpeed.z *= RUN_SPEED;
			}

			else if (m_State == enPlayerJump)
			{

				m_moveSpeed.y = 1.0f;
			}


			//回避の処理
			if (Pad().IsTriggerButton(enButtonRightTrigger))
			{
				m_isSlip = true;
			}

			if (m_isSlip)
			{
				m_slipSpeed = m_slipSpeed - (60.0f * GameTime().GetDeltaFrameTime());
				if (m_slipSpeed <= 0)
				{
					m_isSlip = false;
					m_slipSpeed = 15.0f;
					return;
				}
				CVector3 playerFlontVec = { m_skinmodel.GetWorldMatrix().m[2][0],0.0f,m_skinmodel.GetWorldMatrix().m[2][2] };
				playerFlontVec.Normalize();
				m_moveSpeed = playerFlontVec * m_slipSpeed;
			}

		}

		else
		{

			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
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

	//プレイヤーの手のボーンを取得
	{
		CMatrix PlayerHnd = m_skinmodel.FindBoneWorldMatrix(L"LeftHandMiddle1");

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


		m_WeaponPosition = PlayerHndPos;
		m_WeaponRotation.SetRotation(PlayerHnd);
	}

	//プレイヤーの回転の処理
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
	if (Pad().IsTriggerButton(enButtonX) && m_animation.GetCurrentAnimationNum() != enPlayerAtack)
	{
		m_animation.Play(enPlayerAtack, 0.5f);
		m_State = enPlayerAtack;
	}

	//回避アニメーション
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{

		m_animation.Play(enPlayerAvoidance, 0.5f);
	}

	//ジャンプアニメーションの処理
	else if (Pad().IsTriggerButton(enButtonY) && m_animation.GetCurrentAnimationNum() != enPlayerJump)
	{
		m_animation.Play(enPlayerJump, 0.5);
		m_State = enPlayerJump;

	}

	

	//移動アニメーションの処理
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0 )
	{
		m_animation.SetLoopFlg(enPlayerRun, true);
		m_animation.SetLoopFlg(enPlayerWalk, true);
		CVector3 moveLen = m_characterController.GetMoveSpeed();
		
		float len = moveLen.Length();
		if (len < 0.0)
		{
			len *= -1.0f;
		}
	
	//歩行アニメーション
	 if (len < 2.0f &&m_animation.GetCurrentAnimationNum() != enPlayerWalk)
		{


			m_animation.Play(enPlayerWalk, 0.2);
			m_State = enPlayerWalk;

		}
	 //走りアニメーション
	 else if (len >= 2.0f && m_animation.GetCurrentAnimationNum() != enPlayerRun)
	 {

		 m_animation.Play(enPlayerRun, 0.5);
		 m_State = enPlayerRun;

	 }
	}
	
	//待機モーション
	if (m_animation.GetCurrentAnimationNum() != 0 && Pad().GetLeftStickX() == 0 && Pad().GetLeftStickY() == 0)
	{
		m_animation.SetLoopFlg(1, false);
		if (!m_animation.IsPlay() || m_animation.GetCurrentAnimationNum() == enPlayerRun ||  m_animation.GetCurrentAnimationNum() == enPlayerWalk)
		{

			m_animation.Play(enPlayerStand, 0.2f);
			m_State = enPlayerStand;

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