#include "stdafx.h"
#include "GameCamera.h"
#include "../Player/Player.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"
#include "../Enemy/IEnemy.h"
#include "../Enemy/EnemyGroup.h"
#include "../Enemy/Maw.h"
#include "../Scene/SceneManager.h"
#include "../Map/Map.h"

CGameCamera *CGameCamera::m_gameCamera = NULL;

void CGameCamera::Init()
{
	//カメラの初期化
	m_camera.Init();
	m_camera.SetFar(200.0f);
	m_camera.SetNear(1.0f);
	m_camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	m_camera.SetAngle(CMath::DegToRad(60.0f));
	m_camera.SetPosition({ 0.0f, 1.0f, -3.5f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	m_camera.SetUp({ 0.0f, 1.0f, 0.0f });
	m_camera.Update();
	//Add(this, 0);
	//エンジンにカメラを設定
	Engine().SetCamera(&m_camera);
	//バネカメラの初期化
	m_springCamera.Init(m_camera.GetTarget(), m_camera.GetPosition(), 1000.0f);
	m_springCamera.SetPosition(m_camera.GetPosition());
	m_springCamera.SetTarget(m_camera.GetTarget());
	//揺れカメラの初期化
	m_shakeCamera.Init(CVector3::Zero, CVector3::Zero, {1.0f, 1.0f, 0.0f}, 0.7f);
	//カメラの当たり判定を初期化
	m_cameraCollisionSolver.Init(0.2f);
}

void CGameCamera::CameraSetPlayer()
{
	//注視点を設定する
	CVector3 target = GetPlayer().GetCharacterController().GetPosition();
	target.y += TARGET_OFFSET_Y;
	m_springCamera.SetTarTarget(target);
	//座標を設定する
	CVector3 toCameraPos = { 0.0f, 0.0f, -3.5f };
	CVector3 position = target + toCameraPos;
	m_springCamera.SetTarPosition(position);
	m_springCamera.Update();
	//注視点からカメラまでの距離を求める
	m_cameraLength = toCameraPos.Length();
}

void CGameCamera::Update()
{
	if (&GetPlayer() == nullptr) { return; }
	if(GetPlayer().IsActive() == false) { return; }

	CVector3 target = m_springCamera.GetTarTarget();
	CVector3 position = m_springCamera.GetTarPosition();

	//右スティック押し込みでロックオン
	if (Pad().IsTriggerButton(enButtonRStickPush))
	{
		if (!m_isLockOn) 
		{
			//ロックオンする対象を探す
			SearchTarget();
		}
		else 
		{
			//ロックオンを解除する
			LockOnCancel(target, position);
		}
	}

	//ロックオン中
	if (m_isLockOn)
	{
		//エネミーをロックオンする
		LockOn(target, position);
	}
	else
	{
		//回転させる
		Rotation(target, position);
	}

	////カメラの座標と注視点が近ければ座標と注視点を更新しない
	//float currentHeight = m_camera.GetPosition().y - target.y;
	//if (m_cameraVec.y > 0.0f && currentHeight > 0.0f && fabsf(currentHeight) < m_height)
	//{
	//	target.y = m_camera.GetTarget().y;
	//	position.y = target.y + m_cameraVec.y;
	//}

	//カメラの当たり判定
	CVector3 newPos;
	if (m_cameraCollisionSolver.Execute(newPos, position, target))
	{
		position = newPos;
	}

	//バネカメラを更新する
	m_springCamera.SetTarTarget(target);
	m_springCamera.SetTarPosition(position);
	m_springCamera.Update();
	m_camera.SetTarget(m_springCamera.GetTarget());
	m_camera.SetPosition(m_springCamera.GetPosition());
	//揺れカメラの座標と注視点を設定して更新する
	m_shakeCamera.SetTarget(m_camera.GetTarget());
	m_shakeCamera.SetPosition(m_camera.GetPosition());
	m_shakeCamera.Update();
	//カメラの座標と注視点を設定して更新する
	m_camera.SetTarget(m_shakeCamera.GetShakeTarget());
	m_camera.SetPosition(m_shakeCamera.GetShakePosition());
	m_camera.Update();
}

void CGameCamera::Rotation(CVector3& target, CVector3& position)
{
	//スティックの入力量を取得
	float rStick_x = Pad().GetRightStickX();
	float rStick_y = Pad().GetRightStickY();
	//注視点からカメラまでのベクトルを求める
	CVector3 toCameraPos = position - target;
	toCameraPos.Normalize();
	const float	CAMERA_SPEED = 2.0f;
	if (fabsf(rStick_x) > 0.0f) 
	{
		//Y軸周りの回転
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		matrix.Mul(toCameraPos);
	}
	if (fabsf(rStick_y) > 0.0f)
	{
		//X軸周りの回転
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, toCameraPos);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, rStick_y * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		//1フレーム前のカメラベクトル
		CVector3 cameraVecOld = toCameraPos;
		//カメラから注視点までのベクトルを回転させる
		matrix.Mul(toCameraPos);
		CVector3 cameraDir = toCameraPos;
		cameraDir.Normalize();
		if (cameraDir.y < -0.8f)
		{
			//カメラが下を向きすぎた
			toCameraPos = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f)
		{
			//カメラが上を向きすぎた
			toCameraPos = cameraVecOld;
		}
	}

	//注視点を設定する
	target = GetPlayer().GetCharacterController().GetPosition();
	target.y += TARGET_OFFSET_Y;
	//座標を設定する
	position = target + toCameraPos * m_cameraLength;
}

void CGameCamera::SearchTarget()
{
	if (&GetMaw().GetInstance() != nullptr && m_lockOnState != enLockOn_Boss)
	{
		m_lockOnState = enLockOn_Boss;
		m_isLockOn = true;
		return;
	}
	float minLength = FLT_MAX;
	//エネミーグループのリストを取得
	std::list<CEnemyGroup*> enemyGroupList = GetSceneManager().GetMap()->GetEnemyGroupList();
	for (CEnemyGroup* enemyGroup : enemyGroupList)
	{
		CVector3 enemyGroupPos = enemyGroup->GetPosition();
		CVector3 playerPos = GetPlayer().GetPosition();
		//エネミーグループとプレイヤーの距離を求める
		CVector3 distance = playerPos - enemyGroupPos;
		float length = distance.Length();
		//ロックオンできる距離を設定
		const float	LOCKON_LENGTH = 30.0f;	
		if (length < LOCKON_LENGTH)
		{
			//エネミーグループの中のエネミーリストを取得
			std::list<IEnemy*> enemyList = enemyGroup->GetGroupList();
			for (IEnemy* enemy : enemyList)
			{
				if (enemy->GetIsDead())
				{
					continue;
				}
				CVector3 enemyPos = enemy->GetPosition();
				//エネミーとプレイヤーの距離を求める
				distance = playerPos - enemyPos;
				length = distance.Length();
				if (length < minLength)
				{
					//一番近いエネミーをロックオンする
					m_isLockOn = true;
					minLength = length;
					m_rockOnEnemy = enemy;
					m_lockOnState = enLockOn_Enemy;
				}
			}
		}
	}
}

void CGameCamera::LockOn(CVector3& target, CVector3& position)
{
	CVector3 targetPosition;
	if (m_lockOnState == enLockOn_Boss)
	{
		if (GetMaw().GetSmawStatus().Hp <= 0)
		{
			//ロックオンを外す
			LockOnCancel(target, position);
			return;
		}
		targetPosition = GetMaw().GetPosition();
		targetPosition.y += 3.0f;
	}
	else
	{
		//ロックオンしているエネミーが死亡したか
		if (m_rockOnEnemy->GetIsDead())
		{
			//ロックオンを外す
			LockOnCancel(target, position);
			return;
		}
		targetPosition = m_rockOnEnemy->GetPosition();
		targetPosition.y += 0.5f;
	}

	//ターゲットの座標を注視点に設定
	target = targetPosition;
	//ターゲートからカメラへのベクトルを求める
	CVector3 playerPos = GetPlayer().GetCharacterController().GetPosition();
	CVector3 cameraVec = playerPos - target;
	cameraVec.y = 0.0f;
	//距離を求める
	float length = cameraVec.Length();
	//視点はプレイヤーから一定距離後ろにする
	cameraVec.Normalize();
	cameraVec *= m_cameraLength;
	cameraVec += playerPos;
	cameraVec.y = playerPos.y + LOCKON_OFFSET_Y;
	//ターゲットと近いからカメラの高さに補正をかける
	if (m_lockOnState == enLockOn_Enemy && length < LOCKON_OFFSET_Y)
	{
		//高さは距離が近いほど高い
		cameraVec.y += LOCKON_OFFSET_Y - length;
	}
	//視点に設定
	position = cameraVec;
}

void CGameCamera::LockOnCancel(CVector3& target, CVector3& position)
{
	//ロックオンをやめる
	m_isLockOn = false;
	m_lockOnState = enLockOn_None;
	//現在の注視点からカメラへのベクトルを求める
	CVector3 toCameraPos = position - target;
	toCameraPos.Normalize();
	toCameraPos *= m_cameraLength;
	//注視点を決める
	target = GetPlayer().GetCharacterController().GetPosition();
	target.y += TARGET_OFFSET_Y;
	//座標を決める
	position = target + toCameraPos;
}
