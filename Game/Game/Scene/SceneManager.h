/*
*	シーンマネージャークラス
*/
#pragma once
#include "GameScene.h"
#include "TitleScene.h"

class CSceneManager
{
public:
	enum EnSceneState {
		enTitleScene,	//タイトル
		enGameScene,	//ゲーム
		enResultScene,	//リザルト
		enLoadScene,	//ロード
		enSceneNum		//シーンの数
	};

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


private:
	EnSceneState	m_sceneState= enSceneNum;//シーンのステート（現在のシーンを入れておく用）
	CGameScene*		m_gameScene;			//ゲームシーン
	CTitleScene*	m_titleScene;			//タイトルシーン
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