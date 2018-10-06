#include "stdafx.h"
#include "Zombie.h"
#include"../../Game/Camera/GameCamera.h"

CZombie::CZombie()
{
}

CZombie::~CZombie()
{
}

void CZombie::Init(CVector3 position)
{
	//モデルを読み込む
	m_skinModel.Load(L"Assets/modelData/Zombi.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Zombi_normal.png");
	m_position = position;
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-90.0f);
	wchar_t* animClip[CEnemyState::enState_Num] = { 
		L"Assets/modelData/zombiStand.tka",
		L"Assets/modelData/zombiWalk.tka",
		L"Assets/modelData/zombiDash.tka",
		L"Assets/modelData/zombiAttack.tka",
		L"Assets/modelData/zombiDamage.tka",
		L"Assets/modelData/zombiDeath.tka"
	};
	m_animation.Init(animClip, CEnemyState::enState_Num);
	m_animation.SetLoopFlg(CEnemyState::enState_Idle, true);
	m_animation.SetLoopFlg(CEnemyState::enState_Walk, true);
	m_animation.SetLoopFlg(CEnemyState::enState_Chase, true);
	Add(&m_enemyStateMachine, 0);
	Add(&m_enemyTurn, 0);
	Add(&m_enemySearch, 0);
	//ダメージ表示の初期化
	m_damageNumber.Init();

	//ステータスを設定
	m_status.Strength = 10;
	m_status.Defense = 5;
	m_status.Hp = 50;
	m_status.MaxHp = m_status.Hp;
	m_status.Gold = 100;
}

bool CZombie::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CZombie::Update()
{
	if (!m_isWireHit) {
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
		m_animation.Update(GameTime().GetDeltaFrameTime());
	}
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CZombie::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	m_characterController.Draw();
}
