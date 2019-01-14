#include "stdafx.h"
#include "Ninja.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"

CNinja::CNinja()
{
	this->SetIsActive(false);
}

CNinja::~CNinja()
{
}

void CNinja::OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)
{
	if (wcscmp(animClipName, L"Assets/modelData/NinjaAttack.tka") == 0)
	{
		m_isAttack = !m_isAttack;
	}
}

void CNinja::Init(const CVector3& position)
{
	//モデルを読み込む
	m_skinModel.Load(L"Assets/modelData/Ninja.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Ninja_normal.png");
	m_position = position;
	//キャラクターコントローラーを初期化
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-9.8f);
	//アニメーションの初期化
	wchar_t* animClip[CEnemyState::enAnimation_Num] = {
		L"Assets/modelData/NinjaStand.tka",
		L"Assets/modelData/NinjaWalk.tka",
		L"Assets/modelData/NinjaDash.tka",
		L"Assets/modelData/NinjaAttack.tka",
		L"Assets/modelData/NinjaDamageSmall.tka",
		L"Assets/modelData/NinjaDown.tka",
		L"Assets/modelData/NinjaUp.tka",
		L"Assets/modelData/NinjaDeath.tka"
	};
	m_animation.Init(animClip, CEnemyState::enAnimation_Num);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Idle, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Walk, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Chase, true);
	//Add(&m_enemyStateMachine, 0);
	//Add(&m_enemyTurn, 0);
	//Add(&m_enemySearch, 0);

	//ステータスを設定
	m_status.strength = 10;
	m_status.defense = 0;
	m_status.hp = 50;
	m_status.maxHp = m_status.hp;
	m_status.gold = 100;
	m_status.exp = 10;
	this->SetIsActive(true);

	//腰のワールド行列を取得
	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	//攻撃できる距離を設定
	m_attackLength = 1.2f;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CNinja::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CNinja::Update()
{
	if (m_status.hp <= 0)
	{
		m_isDead = true;
		//剛体を削除する
		m_characterController.RemovedRigidBody();
	}

	if (m_isAttack)
	{
		//攻撃中はプレイヤーとの当たり判定をとる
		//ボーンのワールド行列を取得
		CMatrix boneMatrix = GetBoneWorldMatrix(L"RightFoot");
		CVector3 bonePosition;
		bonePosition.x = boneMatrix.m[3][0];
		bonePosition.y = boneMatrix.m[3][1];
		bonePosition.z = boneMatrix.m[3][2];
		//敵の攻撃との距離を計算
		CVector3 playerPosition = GetPlayer().GetPosition();
		playerPosition.y += 0.5f;
		CVector3 distance = bonePosition - playerPosition;
		float length = distance.Length();
		if (length < 1.0f)
		{
			//プレイヤーがダメージを受けた
			GetPlayer().SetDamage(m_status.strength);
			GetPlayer().SetDamageEnemyPos(m_position);
		}
	}

	if (!m_isWireHit) 
	{
		//アニメーションの更新
		m_animation.Update(GameTime().GetDeltaFrameTime() * 2.0f);
	}

	if (!m_isDead && !m_isWireHit) 
	{
		//座標の更新
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}

	//モデルの更新
 	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CNinja::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CNinja::Attack()
{
	m_animation.Play(CEnemyState::enAnimation_Attack, 0.3f);
}
