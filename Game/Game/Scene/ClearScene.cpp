#include "stdafx.h"
#include "ClearScene.h"
#include "SceneManager.h"

CClearScene::CClearScene()
{
}


CClearScene::~CClearScene()
{
}

bool CClearScene::Start()
{
	//フェードの実行が終わったらtrueを返す
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		const CVector2	clearPos = { -1.0f,-1.0f };		//タイトル座標
		const CVector2	clearSize = { 1280.0f,7200.0f };	//タイトルサイズ

		m_clearTexture = TextureResource().LoadTexture(L"Assets/sprite/TitleBack.png");
		m_clear.Init(m_clearTexture);
		m_clear.SetPosition(clearPos);
		m_clear.SetSize(clearSize);
		//フェードインの開始
		GetSceneManager().GetFade()->FadeIn();
		return true;
	}
	return false;
}

void CClearScene::Update()
{
	if (Pad().IsTriggerButton(enButtonStart) || GetAsyncKeyState('V'))
	{
		//ゲームシーンへ遷移
		GetSceneManager().ChangeScene(GetSceneManager().enTitleScene);

	}
}

void CClearScene::AfterDraw()
{
	m_clear.Draw();
}
