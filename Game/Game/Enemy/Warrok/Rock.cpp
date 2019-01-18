#include "Rock.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../Scene/SceneManager.h"
#include "Warrok.h"

void CRock::Init(CWarrok* warrok, const CVector3& enemyPos)
{
	//モデルを初期化
	m_skinModel.Load(L"Assets/modelData/Rock.cmo");
	//攻撃した敵の座標を保存
	m_enemyPos = enemyPos;
	//座標を初期化
	m_enemyHandMatrix = &warrok->GetBoneWorldMatrix(L"LeftHand");
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
	m_characterController.SetIgnoreRigidBody(&warrok->GetCharacterController().GetBody());
	m_warrok = warrok;

	//パーティクルの初期化
	m_particleInfo.filePath = L"Assets/particle/rockEffect.png";
	m_particleInfo.width = 0.5f;
	m_particleInfo.height = 0.5f;
	m_particleInfo.uv = { 0.0f,0.0f,1.0f,1.0f };
	m_particleInfo.randomPosition = { 0.0f, 0.0f, 0.0f };
	m_particleInfo.gravity = { 0.0f, -9.8f, 0.0f };
	m_particleInfo.lifeTime = 3.0f;
	m_particleInfo.emittIntervalTime = 2.0f;
	m_particleInfo.emitterLifeTime = 1.0f;
	m_particleInfo.emitterPosition = m_position;
	m_particleInfo.moveSpeed = { 0.0f, 5.0f, 0.0f };
	m_particleInfo.randomMoveSpeed = { 3.0f, 3.0f, 3.0f };
	m_particleInfo.particleNum = 10;
	m_particleInfo.isFirstTimeRandom = false;
}

void CRock::Update()
{
	if (GetSceneManager().GetSceneChange() 
		|| (!m_isThrow && (m_warrok->GetStateMachine().GetCurrentState() != CEnemyState::enState_Attack && m_warrok->GetStateMachine().GetCurrentState() != CEnemyState::enState_AttackWait)))
	{
		Delete(this);
	}

	//壁に当たった
	if (m_characterController.GetWallCollisionObject() != nullptr)
	{
		//プレイヤーに当たった
		if(m_characterController.GetWallCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			GetPlayer().SetDamage(m_warrok->GetStatus().strength);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		m_isHit = true;
		Delete(this);
	}

	//地面に当たった
	if (m_characterController.GetGroundCollisionObject() != nullptr)
	{
		//プレイヤーに当たった
		if (m_characterController.GetGroundCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			GetPlayer().SetDamage(m_warrok->GetStatus().strength);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		m_isHit = true;
		Delete(this);
	}

	if (m_isHit)
	{
		//何かに当たっていたらパーティクルを出す
		CParticleEmitter* particleEmitter = New<CParticleEmitter>(PRIORITY_UI);
		particleEmitter->Init(m_particleInfo, &GetGameCamera().GetCamera());
		particleEmitter->SetPosition(m_position);
		m_isHit = false;
	}

	//座標を更新
	if (m_isThrow) 
	{
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}
	else 
	{
		m_position.x = m_enemyHandMatrix->m[3][0];
		m_position.y = m_enemyHandMatrix->m[3][1];
		m_position.z = m_enemyHandMatrix->m[3][2];
	}
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void CRock::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CRock::SetMoveSpeed()
{
	//岩からプレイヤーへのベクトルを求める
	CVector3 distance = GetPlayer().GetPosition() - m_position;
	//XZ平面での距離を求める
	CVector3 distanceXZ = distance;
	distanceXZ.y = 0.0f;
	float lengthXZ = distanceXZ.Length();
	//投げる角度を設定
	float angle = CMath::PI / 6;
	//投げる高さを求める
	float height = tan(angle) * lengthXZ;
	//投げる方向を求める
	CVector3 moveDir = distance;
	moveDir.y += height;
	float length = moveDir.Length();
	moveDir.Normalize();
	//移動速度を設定
	CVector3 moveSpeed;
	moveSpeed.x = moveDir.x * length * cos(angle);
	moveSpeed.y = moveDir.y * length * sin(angle);
	moveSpeed.z = moveDir.z * length * cos(angle);
	m_characterController.SetMoveSpeed(moveSpeed);
}
