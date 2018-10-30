#include "stdafx.h"
#include "Result.h"
#include "../../Player/Player.h"
#include "../../Scene/SceneManager.h"

CResult::CResult()
{
}


CResult::~CResult()
{
}

void CResult::Init()
{
	m_resultTexture.Load(L"Assets/sprite/YouDied.png");
	m_result.Init(&m_resultTexture);
	m_result.SetPosition({ -1.0f, -1.0f });
	m_result.SetSize({ 400.0f,200.0f });
	m_result.SetAlpha(0.0f);
}

void CResult::Update()
{


}
void CResult::AfterDraw()
{
	//プレイヤーが生きているかの判定
	if (!GetPlayer().GetIsDied()) { return; }
	m_alphaTime += GameTime().GetDeltaFrameTime() / 5.0f;
	if (m_alphaTime >= 1.0f)
	{
		m_alphaTime = 1.0f;

		//ゲームシーンに遷移
		GetSceneManager().GetInstance().ChangeScene(GetSceneManager().enGameScene);
	}
	m_result.SetAlpha(m_alphaTime);
	m_result.Draw();

}

void CResult::Draw()
{


}
