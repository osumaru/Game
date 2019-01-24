#include "stdafx.h"
#include "WeekPoint.h"
#include "../../Camera/GameCamera.h"
#include "../../Enemy/Maw.h"
void CWeekPoint::Init()
{
	const CVector2 WeekPos = {0.0f,0.0f};
	const CVector2 WeekSize = {80.0f,80.0f};
	//const float WeekAlpha = 0.7f;
	m_weekTexture = TextureResource().LoadTexture(L"Assets/sprite/arrowTag.png");
	m_weekSprite.Init(m_weekTexture);
	m_weekSprite.SetPosition(WeekPos);
	m_weekSprite.SetSize(WeekSize);
	//m_weekSprite.SetAlpha(WeekAlpha);

	this->SetIsActive(false);
}

void CWeekPoint::Update()
{
	CMatrix ViewMat=GetGameCamera().GetViewMatrix();
	CMatrix ProjMat=GetGameCamera().GetProjectionMatrix();
	CMatrix BossHeadMat = GetMaw().GetBoneMatrix(L"Head");
	CVector3 BossHeadPos;
	BossHeadPos.x = BossHeadMat.m[3][0];
	BossHeadPos.y = BossHeadMat.m[3][1];
	BossHeadPos.z = BossHeadMat.m[3][2];
	//BossPos.y += 15.0f;
	//ビュー変換
	CVector4 viewPos = BossHeadPos;
	ViewMat.Mul(viewPos);

	//プロジェクション変換
	CVector4 projPos = viewPos;
	ProjMat.Mul(projPos);

	projPos = projPos / projPos.w;

	CVector2 screenPos;
	screenPos.x=(1.0f+projPos.x) / 2.0f*FrameBufferWidth() - (FrameBufferWidth() / 2.0f);
	screenPos.y=(1.0f+projPos.y) / 2.0f*FrameBufferHeight() - (FrameBufferHeight() / 2.0f);

	m_weekSprite.SetPosition(screenPos);
}

void CWeekPoint::Draw()
{
	//m_weekSprite.Draw();
}

void CWeekPoint::PostAfterDraw()
{
	//Engine().SetAlphaBlendState(enAlphaBlendStateAdd);
	m_weekSprite.Draw();
	//Engine().SetAlphaBlendState(enAlphaBlendStateNone);
	//m_weekSprite.Draw();
}
