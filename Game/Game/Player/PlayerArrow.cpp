#include "stdafx.h"
#include"../../Game/Camera/GameCamera.h"
#include "PlayerArrow.h"
#include "Player.h"


CPlayerArrow::CPlayerArrow()
{
}


CPlayerArrow::~CPlayerArrow()
{

}

bool CPlayerArrow::Start()
{
	m_arrowskin.Load(L"Assets/modelData/Arrow.cmo", NULL);
	m_light.SetAmbientLight({ 0.0f,0.0f,1.0f ,1.0f });
	m_arrowskin.SetLight(m_light);
	m_scale = { 2.0f,2.0f,2.0f };

	//�v���C���[HP�̃��[�h
	m_texture.Load(L"Assets/sprite/arrowTag.png");
	m_arrowtag.Init(&m_texture);
	m_arrowtag.SetPosition({0.0f,0.0f  });
	m_arrowtag.SetSize({ 50.0f,50.0f });
	m_arrowtag.SetAlpha(1.0f);

	return true;
}

void CPlayerArrow::Update()
{
	//if (GetPlayer().GetPlayerStateMachine().GetState() != CPlayerState::EnPlayerState::enPlayerArrowAttack) { return; }
	if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerArrowAttack && !m_isMove/*Pad().IsPressButton(enButtonX) && !m_isMove*/)
	{
		m_arrowPosition = GetPlayer().GetWeaponPosition();
		CVector3 weaponFlont = GetGameCamera().GetCamera().GetFlont();//{ -mat.m[1][0],-mat.m[1][1],-mat.m[1][2] };
		weaponFlont.Normalize();
		m_moveSpeed = weaponFlont * 10.0f;
		m_arrowRot.SetRotation(CVector3::AxisY, atan2f(weaponFlont.x, weaponFlont.z));		//Y������̉�]
	}
	//����΂�����
	else
	{
		m_isMove = true;
		m_arrowPosition += m_moveSpeed * GameTime().GetDeltaFrameTime();
		m_lifeTime += GameTime().GetDeltaFrameTime();
		
	}
	
	if (m_lifeTime >= 5.0f)
	{
		Delete(this);
		return;
	}
	m_arrowskin.Update(m_arrowPosition, m_arrowRot, m_scale,true);
}

void CPlayerArrow::Draw()
{
	if (!m_isMove)
	{
		m_arrowtag.Draw();
	}
	m_arrowskin.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}