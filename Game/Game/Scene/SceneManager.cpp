#include "stdafx.h"
#include "SceneManager.h"

void CSceneManager::Init()
{
	m_fade = New<CFade>(PRIORITY_MAX - 1);
	m_nextSceneState = enTitleScene;
	//SceneManagerクラスをAdd
	Add(this, 0);
	m_isFadeOut = true;
}

CSceneManager::~CSceneManager()
{

}

void CSceneManager::BeforeDead()
{
	if (m_fade != nullptr)
	{
		Delete(m_fade);
	}
	if (m_gameScene != nullptr)
	{
		Delete(m_gameScene);
	}
	if (m_titleScene != nullptr)
	{
		Delete(m_titleScene);
	}
	if (m_clearScene != nullptr)
	{
		Delete(m_clearScene);
	}

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
			Delete(m_gameScene);
			m_gameScene = nullptr;
			break;
			//クリアシーンの開放
		case EnSceneState::enClearScene:
			Delete(m_clearScene);
			m_clearScene = nullptr;
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
			m_titleScene = New<CTitleScene>(PRIORITY_SCENE);
			break;
			//ゲームシーンへの遷移
		case EnSceneState::enGameScene:
			m_gameScene = New<CGameScene>(PRIORITY_SCENE);
			break;
			//クリアシーンへの遷移
		case EnSceneState::enClearScene:
			m_clearScene = New<CClearScene>(PRIORITY_SCENE);
			break;
			//リザルトシーンへの遷移
		case EnSceneState::enLoadScene:
			//ロード開放の処理をかく
			break;
		default:
			break;
		}
		m_isSceneChange = false;
		//現在のシーンを開放用のステートへ
		m_preSceneState = m_nextSceneState;
	}
}

//シーンの切り替え関数
void CSceneManager::ChangeScene(EnSceneState scene)
{
	//フェードアウトしていなかったら
	if (!m_isFadeOut)
	{
		m_fade->FadeOut();
		m_isFadeOut = true;
	}
	
	m_isSceneChange = true;
	//変更するシーンを現在のシーンにする
	m_nextSceneState = scene;
}