#include "stdafx.h"
#include "Ninja.h"
#include "../Camera/GameCamera.h"

CNinja::CNinja()
{
}

CNinja::~CNinja()
{
}

void CNinja::Init(CVector3 position)
{
	//���f����ǂݍ���
	m_skinModel.Load(L"Assets/modelData/ninja.cmo", &m_animation);
	m_position = position;
	m_initPosition = m_position;
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
	Add(&m_enemyStateMachine, 0);
	Add(&m_enemyTurn, 0);
	Add(&m_enemySearch, 0);
	//�_���[�W�\���̏�����
	m_damageNumber.Init();
}

void CNinja::Update()
{
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_animation.Update(GameTime().GetDeltaFrameTime() * 2.0f);
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CNinja::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
