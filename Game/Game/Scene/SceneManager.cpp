#include "stdafx.h"
#include "SceneManager.h"

void CSceneManager::Init()
{
	m_fade = new CFade;
	Add(m_fade, 15);

	Add(this, 0);
	m_isFadeOut = true;
}

void CSceneManager::Update()
{
	//フェードが呼ばれかつ実行が終わっていたら
	if (m_isFadeOut && !m_fade->IsExecute())
	{
		m_isFadeOut = false;

		//各シーンの開放
		switch (m_preSceneState)
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
		switch (m_nextSceneState)
		{
			//タイトルシーンへの遷移
		case EnSceneState::enTitleScene:
			//初回起動
			if (m_isGameStart)
			{
				m_isGameStart = false;
			}
			else
			{
				//フェードアウトの開始
				GetSceneManager().GetFade()->FadeIn();
			}
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
		//現在のシーンを開放用のステートへ
		m_preSceneState = m_nextSceneState;
	}
}

//シーンの切り替え関数
void CSceneManager::ChangeScene(EnSceneState scene)
{
	//
	if (!m_isFadeOut)
	{
		m_fade->FadeOut();
		m_isFadeOut = true;
	}
	

	//変更するシーンを現在のシーンにする
	m_nextSceneState = scene;


}