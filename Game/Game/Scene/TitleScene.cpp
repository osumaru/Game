#include "stdafx.h"
#include "TitleScene.h"
#include "SceneManager.h"

CTitleScene::CTitleScene()
{

}

CTitleScene::~CTitleScene()
{

}

bool CTitleScene::Start()
{
	//フェードの実行が終わったらtrueを返す
	if (!GetSceneManager().GetFade()->IsExecute())
	{
		const CVector2	titlePos = { -1.0f,-1.0f };		//タイトル座標
		const CVector2	titleSize = { 1280.0f,7200.0f };	//タイトルサイズ

		m_titleTexture.Load(L"Assets/sprite/TitleBack.png");
		m_title.Init(&m_titleTexture);
		m_title.SetPosition(titlePos);
		m_title.SetSize(titleSize);
		//フェードインの開始
		GetSceneManager().GetFade()->FadeIn();
		return true;
	}
	return false;
}

void CTitleScene::Update()
{
	if (Pad().IsTriggerButton(enButtonStart) || GetAsyncKeyState('V'))
	{
		//ゲームシーンへ遷移
		GetSceneManager().ChangeScene(GetSceneManager().enGameScene);
		
	}
}

void CTitleScene::AfterDraw()
{
	m_title.Draw();
}
