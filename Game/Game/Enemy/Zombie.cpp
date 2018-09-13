#include "stdafx.h"
#include "Zombie.h"
#include "../GameCamera.h"

CZombie::CZombie()
{
}

CZombie::~CZombie()
{
}

void CZombie::Init(CVector3 position)
{
	//モデルを読み込む
	m_skinModel.Load(L"Assets/modelData/zombi.cmo", &m_animation);
	m_position = position;
	m_initPosition = m_position;
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-90.0f);
	wchar_t* animClip[5] = { 
		L"Assets/modelData/zombiStand.tka",
		L"Assets/modelData/zombiWalk.tka",
		L"Assets/modelData/zombiAttack.tka",
		L"Assets/modelData/zombiDamage.tka",
		L"Assets/modelData/zombiDeath.tka"
	};
	m_animation.Init(animClip, 5);
	m_animation.SetLoopFlg(0, true);
	m_animation.SetLoopFlg(1, true);
	m_animation.SetLoopFlg(2, true);
	Add(&m_enemyStateMachine, 0);
	Add(&m_enemyTurn, 0);
	Add(&m_enemySearch, 0);
	//ダメージ表示の初期化
	m_damageNumber.Init();
}

void CZombie::Update()
{
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_animation.Update(GameTime().GetDeltaFrameTime());
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CZombie::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
