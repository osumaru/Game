#include "Rock.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"

void CRock::Init(CVector3 position)
{
	//モデルを初期化
	m_skinModel.Load(L"Assets/modelData/Rock.cmo");
	//攻撃した敵の座標を保存
	m_enemyPos = position;
	//座標を初期化
	m_position = position;
	m_position.y += 2.0f;
	//ターゲットの座標(プレイヤーの腰)を設定
	CMatrix playerMatrix = GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Spine");
	m_targetPos.x = playerMatrix.m[3][0];
	m_targetPos.y = playerMatrix.m[3][1];
	m_targetPos.z = playerMatrix.m[3][2];
	//キャラクターコントローラーを初期化
	m_characterController.Init(1.0f, 0.1f, m_position);
	m_characterController.SetGravity(-4.9f);
}

bool CRock::Start()
{
	//岩を投げる方向を求める
	CVector3 attackPos = m_targetPos;
	attackPos.y += 5.0f;
	CVector3 attackDir = attackPos - m_position;
	attackDir.Normalize();
	//投げる角度を設定
	float angle = CMath::PI / 6;
	//ターゲットとの距離を求める
	CVector3 distance = m_targetPos - m_position;
	float length = distance.Length();
	//移動速度を設定
	CVector3 moveSpeed;
	moveSpeed.x = attackDir.x * length * cos(angle);
	moveSpeed.y = attackDir.y * length * sin(angle);
	moveSpeed.z = attackDir.z * length * cos(angle);
	m_characterController.SetMoveSpeed(moveSpeed);

	return true;
}

void CRock::Update()
{
	if (m_characterController.GetWallCollisionObject() != nullptr)
	{
		//壁に当たった
		if(m_characterController.GetWallCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			//プレイヤーに当たった
			GetPlayer().SetDamage(10);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		if (m_characterController.GetWallCollisionObject()->getUserIndex() != enCollisionAttr_Character)
		{
			Delete(this);
		}
	}

	if (m_characterController.GetGroundCollisionObject() != nullptr)
	{
		if (m_characterController.GetGroundCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			//プレイヤーに当たった
			GetPlayer().SetDamage(10);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		//地面に当たった
		Delete(this);
	}

	//座標を更新
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();
	CVector3 modelPos = m_position;
	float offset = 0.2f;
	modelPos.y += offset;
	m_skinModel.Update(modelPos, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void CRock::Draw()
{
	m_characterController.Draw();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
