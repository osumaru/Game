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
	m_scale = { 5.0f,5.0f,5.0f };

	//プレイヤーHPのロード
	m_texture.Load(L"Assets/sprite/arrowTag.png");
	m_arrowtag.Init(&m_texture);
	m_arrowtag.SetPosition({0.0f,0.0f  });
	m_arrowtag.SetSize({ 50.0f,50.0f });
	m_arrowtag.SetAlpha(0.7f);

	return true;
}

void CPlayerArrow::Update()
{
	if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerArrowAttack && !m_isMove)
	{
		m_arrowPosition = GetPlayer().GetWeaponPosition();
		CVector3 weaponFlont = GetGameCamera().GetCamera().GetFlont();//{ -mat.m[1][0],-mat.m[1][1],-mat.m[1][2] };
		weaponFlont.Normalize();
		m_moveSpeed = weaponFlont * 50.0f;
		CQuaternion rotY;
		m_arrowRot.SetRotation(CVector3::AxisY, atan2f(weaponFlont.x, weaponFlont.z));		//Y軸周りの回転
		rotY.SetRotation(CVector3::AxisX, atanf(-weaponFlont.y));		//Y軸周りの回転
		m_arrowRot.Multiply(rotY);
	}
	//矢を飛ばす処理
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