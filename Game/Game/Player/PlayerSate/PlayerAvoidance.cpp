#include "stdafx.h"
#include "PlayerAvoidance.h"
#include "../Player.h"



void CPlayerAvoidance::Init()
{
	m_pPlayer->PlayAnimation(enPlayerAnimationAvoidance, 0.1f);
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
}

void CPlayerAvoidance::Update()
{
	if (!GetPlayer().GetAnimation().IsPlay())
	{
		CMatrix boneMat = GetPlayer().GetPlayerSkin().FindBoneWorldMatrix(L"Hips");
		CVector3 position;
		position = GetPlayer().GetPosition();
		position.x = boneMat.m[3][0];
		position.z = boneMat.m[3][2];
		m_pPlayer->SetPosition(position);

		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);

	}

}
