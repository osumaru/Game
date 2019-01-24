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
	m_toCameraPos = { 0.0f, 0.0f, -3.5f };
	CVector3 position = target + m_toCameraPos;
	m_springCamera.SetTarPosition(position);
	m_springCamera.Update();
	//注視点からカメラまでの距離を求める
	m_cameraLength = m_toCameraPos.Length();
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
			LockOnCancel();
		}
	}

	//ロックオン中
	if (m_isLockOn)
	{
		//ロックオンしているエネミーを切り替える
		ChangeTarget();
		//ロックオンする
		LockOn(target);

		//プレイヤーの座標を取得
		CVector3 playerPos = GetPlayer().GetCharacterController().GetPosition();
		playerPos.y += LOCKON_OFFSET_Y;
		//座標はプレイヤーの座標にカメラへのベクトルを足す
		position = playerPos + m_toCameraPos;
	}
	else
	{
		//弓を装備中でRBボタンを押しているか
		if (m_isArrowZoom)
		{
			//カメラへのベクトルを回転させる
			Rotation();
			//カメラの向いている方向を求める
			CVector3 cameraFront = m_toCameraPos * -1.0f;
			cameraFront.Normalize();
			//注視点はプレイヤーからカメラの向いている方向に一定距離離れた場所
			CVector3 addVec = cameraFront;
			addVec *= 5.0f;
			CVector3 playerPos = GetPlayer().GetCharacterController().GetPosition();
			target = playerPos + addVec;
			target.y += TARGET_OFFSET_Y;
			//上方向を求める
			CVector3 axisY = CVector3::AxisY;
			axisY.Normalize();
			//右方向を求める
			CVector3 rightVec = cameraFront * -1.0f;
			rightVec.Cross(axisY);
			//後方向を求める
			CVector3 backVec = cameraFront * -1.0f;
			backVec *= 1.5f;
			//座標はプレイヤーの後ろから少し右にずれた場所
			position = playerPos + rightVec + backVec;
			position.y += TARGET_OFFSET_Y;
			//注視点の当たり判定
			CVector3 newPos;
			if (m_cameraCollisionSolver.Execute(newPos, target, position))
			{
				target = newPos;
			}
		}
		else
		{
			//カメラへのベクトルを回転させる
			Rotation();
			//注視点と座標を設定
			target = GetPlayer().GetCharacterController().GetPosition();
			target.y += TARGET_OFFSET_Y;
			position = target + m_toCameraPos;
		}
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

void CGameCamera::Rotation()
{
	//スティックの入力量を取得
	float rStick_x = Pad().GetRightStickX();
	float rStick_y = Pad().GetRightStickY();
	//カメラの回転スピード
	const float	ROT_SPEED = 2.0f;
	if (fabsf(rStick_x) > 0.0f) 
	{
		//Y軸周りの回転
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x * ROT_SPEED * GameTime().GetDeltaFrameTime());
		matrix.Mul(m_toCameraPos);
	}
	if (fabsf(rStick_y) > 0.0f)
	{
		//X軸周りの回転
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, m_toCameraPos);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, rStick_y * ROT_SPEED * GameTime().GetDeltaFrameTime());
		//1フレーム前のカメラベクトル
		CVector3 cameraVecOld = m_toCameraPos;
		//カメラから注視点までのベクトルを回転させる
		matrix.Mul(m_toCameraPos);
		CVector3 cameraDir = m_toCameraPos;
		cameraDir.Normalize();
		if (cameraDir.y < -0.8f)
		{
			//カメラが下を向きすぎた
			m_toCameraPos = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f)
		{
			//カメラが上を向きすぎた
			m_toCameraPos = cameraVecOld;
		}
	}
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
	if (enemyGroupList.empty())
	{
		return;
	}
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
			std::list<SEnemyGroupData> enemyList = enemyGroup->GetGroupList();
			for (SEnemyGroupData& enemyData : enemyList)
			{
				if (enemyData.enemy->GetIsDead())
				{
					continue;
				}
				CVector3 enemyPos = enemyData.enemy->GetPosition();
				//エネミーとプレイヤーの距離を求める
				distance = playerPos - enemyPos;
				length = distance.Length();
				if (length < minLength)
				{
					//一番近いエネミーをロックオンする
					m_isLockOn = true;
					minLength = length;
					m_lockOnEnemy = enemyData.enemy;
					m_lockOnEnemyNumber = enemyData.groupNumber;
					m_lockOnState = enLockOn_Enemy;
				}
			}
		}
	}
}

void CGameCamera::ChangeTarget()
{
	float rStick_x = Pad().GetRightStickX();
	//右スティックを入力したか
	if (rStick_x == 0.0f)
	{
		//右スティックを入力していない
		return;
	}
	//ロックオン対象がボスであるか
	if (m_lockOnState == enLockOn_Boss)
	{
		//ターゲットを切り替える
		SearchTarget();
		return;
	}

	//ロックオン対象のエネミーグループのリストを取得
	std::list<SEnemyGroupData> enemyGroup = m_lockOnEnemy->GetEnemyGroup()->GetGroupList();
	if (m_lockOnState != enLockOn_Enemy && enemyGroup.empty())
	{
		return;
	}
	//右にスティックを倒すとプラス
	if (rStick_x > 0.0f)
	{
		m_lockOnEnemyNumber++;
		//グループの数より大きければ最初の番号にする
		if (m_lockOnEnemyNumber > m_lockOnEnemy->GetEnemyGroup()->GetGroupNum())
		{
			m_lockOnEnemyNumber = 1;
		}
	}
	//左にスティックを倒すとマイナス
	else if (rStick_x < 0.0f)
	{
		m_lockOnEnemyNumber--;
		//番号が一番小さければ最後の番号にする
		if (m_lockOnEnemyNumber < 1)
		{
			m_lockOnEnemyNumber = m_lockOnEnemy->GetEnemyGroup()->GetGroupNum();
		}
	}

	for (auto& enemyData : enemyGroup)
	{
		//同じ番号の敵をロックオン対象とする
		if (enemyData.groupNumber == m_lockOnEnemyNumber)
		{
			m_lockOnEnemy = enemyData.enemy;
			break;
		}
	}
}

void CGameCamera::LockOn(CVector3& target)
{
	if (m_lockOnState == enLockOn_Boss)
	{
		if (GetMaw().GetSmawStatus().Hp <= 0)
		{
			//ロックオンを外す
			LockOnCancel();
			return;
		}
		target = GetMaw().GetPosition();
		target.y += 3.0f;
	}
	else
	{
		//ロックオンしているエネミーが死亡したか
		if (m_lockOnEnemy->GetIsDead())
		{
			//ロックオンを外す
			LockOnCancel();
			return;
		}
		target = m_lockOnEnemy->GetPosition();
		target.y += 0.5f;
	}

	//ターゲートからカメラへのベクトルを求める
	CVector3 playerPos = GetPlayer().GetCharacterController().GetPosition();
	CVector3 cameraVec = playerPos - target;
	cameraVec.y = 0.0f;
	//距離を求める
	float length = cameraVec.Length();
	//ターゲットと近いからカメラの高さに補正をかける
	if (m_lockOnState == enLockOn_Enemy && length < LOCKON_OFFSET_Y)
	{
		//高さは距離が近いほど高い
		cameraVec.y += LOCKON_OFFSET_Y - length;
	}
	//視点はプレイヤーから一定距離後ろにする
	cameraVec.Normalize();
	cameraVec *= m_cameraLength;
	m_toCameraPos = cameraVec;
}

void CGameCamera::LockOnCancel()
{
	//ロックオンをやめる
	m_isLockOn = false;
	m_lockOnState = enLockOn_None;
}
