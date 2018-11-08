/*
*	シーンマネージャークラス
*/
#pragma once
#include "GameScene.h"
#include "TitleScene.h"
#include "ClearScene.h"
#include "../UI/Fade/Fade.h"

class CSceneManager:public IGameObject
{
public:
	enum EnSceneState {
		enTitleScene,	//タイトル
		enGameScene,	//ゲーム
		enLoadScene,	//ロード
		enClearScene,	//クリア
		enSceneNum		//シーンの数
	};

	//初期化
	void Init();

	//更新
	void Update();

	//シーン変化
	//scene		遷移したいシーン
	void ChangeScene(EnSceneState scene);

	//ゲームシーンの取得
	CGameScene& GetGameScene()
	{
		return *m_gameScene;
	}

	//シーンマネージャーのインスタンスを取得
	static CSceneManager& GetInstance()
	{
		static CSceneManager sceneManager;
		return sceneManager;
	}
	//フェードの取得
	CFade* GetFade()
	{
		return m_fade;
	}

	//フェードアウトが開始したか
	bool GetFadeOut()
	{
		return m_isFadeOut;
	}

private:
	EnSceneState	m_preSceneState= enSceneNum;//シーンのステート（現在のシーンを入れておく用）
	EnSceneState	m_nextSceneState = enSceneNum;//シーンのステート（次のシーンを入れておく用）
	CGameScene*		m_gameScene=nullptr;			//ゲームシーン
	CTitleScene*	m_titleScene = nullptr;			//タイトルシーン
	CClearScene*	m_clearScene = nullptr;			//クリアシーン
	CFade*			m_fade;					//フェイド

	bool			m_isFadeOut = false;		//フェードアウトしたかどうか
	//bool			m_isGameStart = true;			//初回起動時かどうか
	//IScene*			m_scene;			//シーンのインターフェース
};

//シーンマネージャーのインスタンスを取得
static CSceneManager& GetSceneManager()
{
	return CSceneManager::GetInstance();
}

//ゲームシーンの取得
static CGameScene& GetSceneGame()
{
	return GetSceneManager().GetGameScene();
}

//フェードの取得
//static CFade& Fade()
//{
//	return GetSceneManager().GetFade();
//}