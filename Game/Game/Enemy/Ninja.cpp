#include "stdafx.h"
#include "Ninja.h"
#include "../GameCamera.h"

CNinja::CNinja()
{
}

CNinja::~CNinja()
{
}

void CNinja::Init(CVector3 position)
{
	//モデルを読み込む
	m_skinModel.Load(L"Assets/modelData/ninja.cmo", &m_animation);
	m_position = position;
	m_rotation.SetRotationDeg(CVector3::AxisX, -90.0f);
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-90.0f);
	wchar_t* animClip[5] = {
		L"Assets/modelData/ninjaStand.tka",
		L"Assets/modelData/ninjaWalk.tka",
		L"Assets/modelData/ninjaAttack.tka",
		L"Assets/modelData/ninjaDamage.tka",
		L"Assets/modelData/ninjaDeath.tka"
	};
	m_animation.Init(animClip, 5);
	m_animation.SetLoopFlg(0, true);
	m_animation.SetLoopFlg(1, true);
	m_animation.SetLoopFlg(2, true);
	Add(&m_enemyStateMachine, 0);
	//ダメージ表示の初期化
	m_damageNumber.Init();
}

void CNinja::Update()
{
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_animation.Update(GameTime().GetDeltaFrameTime());
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void CNinja::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
