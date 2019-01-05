#include "stdafx.h"
#include "GameCamera.h"
#include "../Player/Player.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"
#include "../Enemy/IEnemy.h"
#include "../Enemy/EnemyGroup.h"
#include "../Scene/SceneManager.h"
#include "../Map/Map.h"

CGameCamera *CGameCamera::m_gameCamera = NULL;

void CGameCamera::Init()
{
	//カメラの初期化
	m_camera.Init();
	m_camera.SetFar(300.0f);
	m_camera.SetNear(1.0f);
	m_camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	m_camera.SetAngle(CMath::DegToRad(60.0f));
	m_camera.SetPosition({ 0.0f, 0.0f, 3.5f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	m_camera.SetUp({ 0.0f, 1.0f, 0.0f });
	m_camera.Update();
	//Add(this, 0);
	//注視点からカメラへのベクトルを求める
	m_cameraVec = m_camera.GetPosition() - m_camera.GetTarget();
	//物理ワールドにカメラを設定
	PhysicsWorld().SetCamera(&m_camera);
	//エンジンにカメラを設定
	Engine().GetDeferred().SetCamera(&m_camera);
	Engine().GetEffectEngine().SetCamera(&m_camera);
	Sky().Init(&m_camera);
	//バネカメラの初期化
	m_springCamera.Init(m_camera.GetTarget(), m_camera.GetPosition(), 1000.0f);
	m_springCamera.SetDampingRate(0.7f);
	m_springCamera.SetPosition(m_camera.GetPosition());
	m_springCamera.SetTarget(m_camera.GetTarget());
	//揺れカメラの初期化
	m_shakeCamera.Init(CVector3::Zero, CVector3::Zero, {1.0f, 1.0f, 0.0f}, 0.7f);
}

void CGameCamera::CameraSetPlayer()
{
	m_pPlayerBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Spine2");
}

void CGameCamera::Update()
{
	if (&GetPlayer() == nullptr) { return; }
	if(GetPlayer().IsActive() == false) { return; }

	//回転させる
	Rotation();
	//注視点を設定する
	CVector3 target;
	target.x = m_pPlayerBoneMat->m[3][0];
	target.y = m_pPlayerBoneMat->m[3][1];
	target.z = m_pPlayerBoneMat->m[3][2];
	//座標を設定する
	CVector3 position = target + m_cameraVec;

	//右スティック押し込みでロックオン
	if (Pad().IsTriggerButton(enButtonRStickPush))
	{
		//エネミーをロックオンする
		RockOnEnemy();
	}
	//ロックオン中
	if (m_isRockOn)
	{
		//ロックオンしているエネミーが死亡したか
		if (m_rockOnEnemy->GetStatus().hp <= 0)
		{
			//ロックオンを外す
			m_isRockOn = false;
		}
		else 
		{
			//カメラの注視点を設定
			target = m_rockOnEnemy->GetPosition();
			//カメラの座標を求める
			CVector3 playerPos = GetPlayer().GetPosition();
			CVector3 targetPos = m_camera.GetTarget();
			CVector3 cameraPos = playerPos - targetPos;
			cameraPos.Normalize();
			cameraPos *= 2.0f;
			cameraPos += playerPos;
			cameraPos.y += 2.5f;
			//カメラの座標を設定
			position = cameraPos;
		}
	}

	//バネカメラを更新する
	m_springCamera.SetTarTarget(target);
	m_springCamera.SetTarPosition(position);
	m_springCamera.Update();
	m_camera.SetPosition(m_springCamera.GetPosition());
	m_camera.SetTarget(m_springCamera.GetTarget());
	//揺れカメラの座標と注視点を設定して更新する
	m_shakeCamera.SetPosition(m_camera.GetPosition());
	m_shakeCamera.SetTarget(m_camera.GetTarget());
	m_shakeCamera.Update();
	//カメラの座標と注視点を設定して更新する
	m_camera.SetPosition(m_shakeCamera.GetShakePosition());
	m_camera.SetTarget(m_shakeCamera.GetShakeTarget());
	m_camera.Update();
}

void CGameCamera::Rotation()
{
	//スティックの入力量を取得
	float rStick_x = Pad().GetRightStickX();
	float rStick_y = Pad().GetRightStickY();
	//注視点からカメラまでのベクトルを求める
	m_cameraVec = m_camera.GetPosition() - m_camera.GetTarget();
	if (fabsf(rStick_x) > 0.0f) 
	{
		//Y軸周りの回転
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		matrix.Mul(m_cameraVec);
	}
	if (fabsf(rStick_y) > 0.0f)
	{
		//X軸周りの回転
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, m_cameraVec);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, rStick_y * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		//1フレーム前のカメラベクトル
		CVector3 cameraVecOld = m_cameraVec;
		//カメラから注視点までのベクトルを回転させる
		matrix.Mul(m_cameraVec);
		CVector3 cameraDir = m_cameraVec;
		cameraDir.Normalize();
		if (cameraDir.y < -0.8f)
		{
			//カメラが下を向きすぎた
			m_cameraVec = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f)
		{
			//カメラが上を向きすぎた
			m_cameraVec = cameraVecOld;
		}
	}
	m_cameraVec.Normalize();
	m_cameraVec.Scale(3.5f);
}

void CGameCamera::RockOnEnemy()
{
	if (m_isRockOn)
	{
		//ロックオンしてるから外す
		m_isRockOn = false;
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
		if (length < 30.0f)
		{
			//エネミーグループの中のエネミーリストを取得
			std::list<IEnemy*> enemyList = enemyGroup->GetGroupList();
			for (IEnemy* enemy : enemyList)
			{
				CVector3 enemyPos = enemy->GetPosition();
				//エネミーとプレイヤーの距離を求める
				distance = playerPos - enemyPos;
				length = distance.Length();
				if (length < minLength)
				{
					//ロックオンする
					m_isRockOn = true;
					minLength = length;
					m_rockOnEnemy = enemy;
				}
			}
		}
	}
}