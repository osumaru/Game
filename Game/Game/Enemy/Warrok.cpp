#include "stdafx.h"
#include "Warrok.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"
#include "PathFinding/RootPoint.h"
#include "PathFinding/PathFinding.h"

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
	wchar_t* animClip[CEnemyState::enState_Num] = {
		L"Assets/modelData/warrokStand.tka",
		L"Assets/modelData/warrokWalk.tka",
		L"Assets/modelData/warrokDash.tka",
		L"Assets/modelData/warrokAttack.tka",
		L"Assets/modelData/warrokDamage.tka",
		L"Assets/modelData/warrokDeath.tka"
	};
	m_animation.Init(animClip, CEnemyState::enState_Num);
	m_animation.SetLoopFlg(CEnemyState::enState_Idle, true);
	m_animation.SetLoopFlg(CEnemyState::enState_Walk, true);
	m_animation.SetLoopFlg(CEnemyState::enState_Chase, true);
	Add(&m_enemyStateMachine, 0);
	Add(&m_enemyMove, 0);
	Add(&m_enemyTurn, 0);
	Add(&m_enemySearch, 0);
	//ダメージ表示の初期化
	m_damageNumber.Init();

	//ステータスを設定
	m_status.Strength = 10;
	m_status.Defense = 0;
	m_status.Hp = 50;
	m_status.MaxHp = m_status.Hp;
	m_status.Gold = 100;
}

bool CWarrok::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CWarrok::Update()
{
	//if (m_isFind && m_rootPoint != nullptr) {
	//	//見つかっていれば経路探索する
	//	std::vector<CVector2> root;
	//	g_pathFinding.FindRoot(root, m_rootPoint->GetListNumber(), GetPlayer().GetRootPoint()->GetListNumber());
	//	if (!root.empty()) {
	//		CVector3 moveSpeed = { root[0].x, 0.0f, root[0].y };
	//		CVector3 pos = m_position;
	//		pos.y = 0.0f;
	//		moveSpeed -= pos;
	//		moveSpeed.Normalize();
	//		moveSpeed *= 2.0f;
	//		m_characterController.SetMoveSpeed(moveSpeed);
	//	}
	//}

	if (!m_isWireHit) {
		m_animation.Update(GameTime().GetDeltaFrameTime());
	}
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CWarrok::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
