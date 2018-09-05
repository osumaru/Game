#include "stdafx.h"
#include "RecoveryItem.h"
#include "../GameCamera.h"
#include "../Player/Player.h"

void CRecoveryItem::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/heart.cmo");
	m_position = position;
}

void CRecoveryItem::Update()
{
	CVector3 toPlayer = m_position - GetPlayer().GetPosition();
	float length = toPlayer.Length();
	if (length < 10.0f) {
		Dead();
	}

	CQuaternion rotation;
	m_skinModel.Update(m_position, rotation, { 1.0f,1.0f,1.0f });
}

void CRecoveryItem::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
