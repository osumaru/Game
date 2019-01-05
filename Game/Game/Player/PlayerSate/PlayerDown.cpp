#include "stdafx.h"
#include "PlayerDown.h"
#include "PlayerState.h"
#include "../Player.h"

CPlayerDown::CPlayerDown()
{
}


CPlayerDown::~CPlayerDown()
{
}

void CPlayerDown::Init()
{
	//アニメーションの再生
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDown, 0.2f);
}

void CPlayerDown::Update()
{
	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
	////m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	//CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
	//moveSpeed.x = 0.0f;
	//moveSpeed.z = 0.0f;
	//m_pPlayerGetter->SetMoveSpeed(moveSpeed);
	if (!m_pPlayerGetter->GetAnimation().IsPlay()&& m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() == enPlayerAnimationUp)
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
	else if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		//CVector3 playerPos = m_pPlayer->GetPosition();
		//CMatrix spineMatrix = m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"Spine");
		//CVector3 position;
		//position.x = spineMatrix.m[3][0];
		////position.y = spineMatrix.m[3][1];
		//position.y = playerPos.y;
		//position.z = spineMatrix.m[3][2];
		//m_pPlayerGetter->SetPosition(position);
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationUp, 0.2f);
	}
}
