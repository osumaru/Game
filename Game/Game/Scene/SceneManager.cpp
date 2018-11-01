#include "stdafx.h"
#include "SceneManager.h"

//シーンの切り替え関数
void CSceneManager::ChangeScene(EnSceneState scene)
{

	//各シーンの開放
	switch (m_sceneState)
	{
		//タイトルシーンの開放
	case EnSceneState::enTitleScene:
		Delete(m_titleScene);
		m_titleScene = nullptr;
		break;
		//ゲームシーンの開放
	case EnSceneState::enGameScene:
		m_gameScene->Release();
		Delete(m_gameScene);
		m_gameScene = nullptr;
		break;
		//リザルトシーンの開放
	case EnSceneState::enResultScene:
		//リザルト開放の処理をかく
		break;
		//ロードシーンの開放
	case EnSceneState::enLoadScene:
		//ロード開放の処理をかく
		break;
	default:
		break;
	}



	//各シーンへの遷移
	switch (scene)
	{
		//タイトルシーンへの遷移
	case EnSceneState::enTitleScene:
		m_titleScene = New<CTitleScene>(0);
		m_titleScene->Init();
		break;
		//ゲームシーンへの遷移
	case EnSceneState::enGameScene:
		m_gameScene = New<CGameScene>(0);
		m_gameScene->Init();
		break;
		//リザルトシーンへの遷移
	case EnSceneState::enResultScene:
		break;
		//リザルトシーンへの遷移
	case EnSceneState::enLoadScene:
		//ロード開放の処理をかく
		break;
	default:
		break;
	}

	//変更したシーンを現在のシーンにする
	m_sceneState = scene;
}