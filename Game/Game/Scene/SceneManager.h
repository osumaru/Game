#pragma once
#include "GameScene.h"

enum enSeceneState 
{
	enTitleScene,
	enGameScene

};

class CSceneManager : public IGameObject
{
public:
	enum EnSceneState {
		enGameScene,	//ゲーム
		enResultScene,	//リザルト
		enTitleScene,	//タイトル
	};

	//初期化
	void Init();

	//更新
	void Update();

	//シーン変化
	void ChangeScene(EnSceneState scene);

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

	//初期化が終わったかを設定
	void SetEndInit(bool endinit)
	{
		m_isEndInit = endinit;
	}

	//初期化が終わったかを取得
	bool GetEndInit()
	{
		return m_isEndInit;
	}

private:


	CGameScene		m_gameScene;			//ゲームシーン
	bool			m_isEndInit = false;	//初期化しているかどうか

};

static CSceneManager& GetSceneManager()
{

	return CSceneManager::GetInstance();
}
