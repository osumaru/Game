#include "stdafx.h"
#include "Warrok.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"

CWarrok::CWarrok()
{
}

CWarrok::~CWarrok()
{
}

void CWarrok::Init(CVector3 position)
{
	//モデルを読み込む
	m_skinModel.Load(L"Assets/modelData/Warrok.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Warrok_normal.png");
	m_position = position;
	m_characterController.Init(0.5f, 0.9f, position);
	m_characterController.SetGravity(-90.0f);
	wchar_t* animClip[CEnemyState::enState_Num] = {
		L"Assets/modelData/warrokStand.tka",
		L"Assets/modelData/warrokWalk.tka",
		L"Assets/modelData/warrokDash.tka",
		L"Assets/modelData/warrokAttack.tka",
		L"Assets/modelData/warrokDamageSmall.tka",
		L"Assets/modelData/warrokDeath.tka"
	};
	m_animation.Init(animClip, CEnemyState::enState_Num);
	m_animation.SetLoopFlg(CEnemyState::enState_Idle, true);
	m_animation.SetLoopFlg(CEnemyState::enState_Walk, true);
	m_animation.SetLoopFlg(CEnemyState::enState_Chase, true);
	Add(&m_enemyStateMachine, 0);
	Add(&m_enemyTurn, 0);
	Add(&m_enemySearch, 0);

	//ステータスを設定
	m_status.strength = 10;
	m_status.defense = 0;
	m_status.hp = 50;
	m_status.maxHp = m_status.hp;
	m_status.gold = 100;
	m_status.exp = 10;
}

bool CWarrok::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CWarrok::Update()
{
	if (!m_isWireHit) {
		m_animation.Update(GameTime().GetDeltaFrameTime());
	}
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CWarrok::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
