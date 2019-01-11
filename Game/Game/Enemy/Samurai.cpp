#include "stdafx.h"
#include "Samurai.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"

CSamurai::CSamurai()
{
	this->SetIsActive(false);
}

CSamurai::~CSamurai()
{
}

void CSamurai::Init(CVector3 position)
{
	//モデルを読み込む
	m_skinModel.Load(L"Assets/modelData/Samurai.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Samurai_normal.png");
	m_position = position;
	//キャラクターコントローラーを初期化
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-9.8f);
	//アニメーションの更新
	wchar_t* animClip[CEnemyState::enAnimation_Num] = {
		L"Assets/modelData/SamuraiStand.tka",
		L"Assets/modelData/SamuraiWalk.tka",
		L"Assets/modelData/SamuraiDash.tka",
		L"Assets/modelData/SamuraiAttack.tka",
		L"Assets/modelData/SamuraiDamage.tka",
		L"Assets/modelData/SamuraiDown.tka",
		L"Assets/modelData/SamuraiUp.tka",
		L"Assets/modelData/SamuraiDeath.tka"
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
}

bool CSamurai::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CSamurai::Update()
{
	//当たり判定用の腰の座標を更新
	UpdateSpinePos();

	if (!m_isWireHit) {
		//アニメーションの更新
		m_animation.Update(GameTime().GetDeltaFrameTime());
	}

	if (!m_isRemovedRigidBody && !m_isWireHit) {
		//座標の更新
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}

	//モデルの更新
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CSamurai::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CSamurai::Attack()
{
	m_animation.Play(CEnemyState::enAnimation_Attack, 0.3f);
}
