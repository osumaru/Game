#include "stdafx.h"
#include "SceneManager.h"



void CSceneManager::Init()
{

	m_gameScene.Init();

}

void CSceneManager::Update()
{

}

void CSceneManager::ChangeScene(EnSceneState scene)
{
	//ゲームシーンが初期化されていたら
	if (m_isEndInit)
	{
		m_gameScene.Release();
	}
	//m_gameScene.Release();
	switch (scene)
	{
	//タイトルシーンへの遷移
	case EnSceneState::enTitleScene:
		break;
	//ゲームシーンへの遷移
	case EnSceneState::enGameScene:
		m_gameScene.Init();
		break;
	//リザルトシーンへの遷移
	case EnSceneState::enResultScene:
		break;
	}
}