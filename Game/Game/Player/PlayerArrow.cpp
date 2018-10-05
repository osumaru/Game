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
	m_scale = { 1.0f,1.0f,1.0f };
	return true;
}

void CPlayerArrow::Update()
{
	m_arrowPosition = GetPlayer().GetPosition();
	m_arrowskin.Update(m_arrowPosition, m_arrowRot, m_scale,false);
}

void CPlayerArrow::Draw()
{

	m_arrowskin.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}