#include "stdafx.h"
#include "TitleScene.h"
#include "../../Scene/SceneManager.h"

void CTitleScene::Init()
{
	m_titleTexture.Load(L"Assets/sprite/YouDied.png");
	m_title.Init(&m_titleTexture);
	m_title.SetPosition({ -1.0f, -1.0f });
	m_title.SetSize({ 400.0f,200.0f });
	m_title.SetAlpha(0.0f);
}

void CTitleScene::Update()
{
	if (Pad().IsTriggerButton(enButtonSelect))
	{
		//ƒQ[ƒ€ƒV[ƒ“‚Ö‘JˆÚ
		GetSceneManager().ChangeScene(GetSceneManager().enGameScene);
	}
}

void CTitleScene::AfterDraw()
{
	m_title.Draw();
}
