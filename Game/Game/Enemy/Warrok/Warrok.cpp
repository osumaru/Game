#include "stdafx.h"
#include "Warrok.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"
#include "Rock.h"

CWarrok::CWarrok()
{
	this->SetIsActive(false);
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
	m_characterController.SetGravity(-9.0f);
	wchar_t* animClip[CEnemyState::enAnimation_Num] = {
		L"Assets/modelData/WarrokStand.tka",
		L"Assets/modelData/WarrokWalk.tka",
		L"Assets/modelData/WarrokDash.tka",
		L"Assets/modelData/WarrokAttack.tka",
		L"Assets/modelData/WarrokDamageSmall.tka",
		L"Assets/modelData/WarrokDown.tka",
		L"Assets/modelData/WarrokUp.tka",
		L"Assets/modelData/WarrokDeath.tka"
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

	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	m_attackLength = 10.0f;
	m_attackType = enAttackType_Far;
}

bool CWarrok::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CWarrok::Update()
{
	UpdateSpinePos();

	if (!m_isWireHit) {
		m_animation.Update(GameTime().GetDeltaFrameTime());
	}

	if (!m_isRemovedRigidBody && !m_isWireHit) {
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}

	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CWarrok::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CWarrok::Attack()
{
	CVector3 toPlayer = GetPlayer().GetPosition() - m_position;
	toPlayer.y = 0.0f;
	float length = toPlayer.Length();
	if (length > 4.0f)
	{
		CRock* rock = New<CRock>(PRIORITY_ENEMY);
		rock->Init(m_position);
	}
}
