#include "stdafx.h"
#include "PlayerAvoidance.h"
#include "../Player.h"



void CPlayerAvoidance::Init()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerAvoidance, 0.1f);
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
		GetPlayer().SetPosition(position);
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
		GetPlayer().SetAnimationPlay(CPlayer::enPlayerStand, 0.1f);

	}

}
