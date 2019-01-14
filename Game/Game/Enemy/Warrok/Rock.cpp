#include "Rock.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../Scene/SceneManager.h"
#include "../IEnemy.h"

void CRock::Init(IEnemy* enemy, CVector3 enemyPos)
{
	//モデルを初期化
	m_skinModel.Load(L"Assets/modelData/Rock.cmo");
	//攻撃した敵の座標を保存
	m_enemyPos = enemyPos;
	//座標を初期化
	m_enemyHandMatrix = &enemy->GetBoneWorldMatrix(L"LeftHand");
	m_position.x = m_enemyHandMatrix->m[3][0];
	m_position.y = m_enemyHandMatrix->m[3][1];
	m_position.z = m_enemyHandMatrix->m[3][2];
	//ターゲットの座標(プレイヤーの腰)を設定
	CMatrix playerMatrix = GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Spine");
	m_targetPos.x = playerMatrix.m[3][0];
	m_targetPos.y = playerMatrix.m[3][1];
	m_targetPos.z = playerMatrix.m[3][2];
	//キャラクターコントローラーを初期化
	m_characterController.Init(1.0f, 0.1f, m_position);
	m_characterController.SetGravity(-4.9f);
	m_characterController.SetIgnoreRigidBody(&enemy->GetCharacterController().GetBody());
	m_enemy = enemy;
}

void CRock::Update()
{
	if (GetSceneManager().GetSceneChange() 
		|| (!m_isThrow && m_enemy->GetIsDamage()))
	{
		Delete(this);
	}
	if (m_characterController.GetWallCollisionObject() != nullptr)
	{
		if(m_characterController.GetWallCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			//プレイヤーに当たった
			GetPlayer().SetDamage(m_enemy->GetStatus().strength);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		//壁に当たった
		Delete(this);
	}

	if (m_characterController.GetGroundCollisionObject() != nullptr)
	{
		if (m_characterController.GetGroundCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			//プレイヤーに当たった
			GetPlayer().SetDamage(m_enemy->GetStatus().strength);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		//地面に当たった
		Delete(this);
	}

	//座標を更新
	if (m_isThrow) {
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}
	else {
		m_position.x = m_enemyHandMatrix->m[3][0];
		m_position.y = m_enemyHandMatrix->m[3][1];
		m_position.z = m_enemyHandMatrix->m[3][2];
	}
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void CRock::Draw()
{
	m_characterController.Draw();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
