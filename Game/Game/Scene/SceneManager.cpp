#include "stdafx.h"
#include "SceneManager.h"



void CSceneManager::Init()
{
	//ゲームシーン
	m_gameScene.Init();
	m_sceneState = enGameScene;

	//タイトルシーンの初期化
	//m_titleScene.Init();
	//m_sceneState = enTitleScene;
}

void CSceneManager::Update()
{

}

//シーンの切り替え関数
void CSceneManager::ChangeScene(EnSceneState scene)
{
	//後々継承とかポリモーなんちゃらを使った処理に変える？

	//各シーンの開放
	switch (m_sceneState)
	{
		//タイトルシーンの開放
	case EnSceneState::enTitleScene:
		//タイトル開放の処理をかく
		break;
		//ゲームシーンの開放
	case EnSceneState::enGameScene:
		m_gameScene.Release();
		break;
		//リザルトシーンの開放
	case EnSceneState::enResultScene:
		//リザルト開放の処理をかく
		break;
	default:
		break;
	}

	//各シーンへの遷移
	switch (scene)
	{
		//タイトルシーンへの遷移
	case EnSceneState::enTitleScene:
		m_titleScene.Init();
		break;
		//ゲームシーンへの遷移
	case EnSceneState::enGameScene:
		m_gameScene.Init();
		break;
		//リザルトシーンへの遷移
	case EnSceneState::enResultScene:
		break;
	default:
		break;
	}
}