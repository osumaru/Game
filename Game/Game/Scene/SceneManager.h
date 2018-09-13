#pragma once
#include "GameScene.h"


class CSceneManager : public IGameObject
{
public:


	void Init();

	void Update();

	//ゲームシーンの取得
	CGameScene& GetGameScene()
	{
		return m_gameScene;
	}

	//シーンマネージャーのインスタンスを取得
	static CSceneManager& GetInstance()
	{
		static CSceneManager sceneManager;
		return sceneManager;
	}

private:


	CGameScene		m_gameScene;	//ゲームシーン

};

static CSceneManager& GetSceneManager()
{

	return CSceneManager::GetInstance();
}
