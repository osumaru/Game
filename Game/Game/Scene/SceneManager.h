/*
*	シーンマネージャークラス
*/
#pragma once
#include "GameScene.h"
#include "TitleScene.h"
#include "ClearScene.h"
#include "BossScene.h"
#include "../UI/Fade/Fade.h"

class CSceneManager:public IGameObject
{
public:
	enum EnSceneState {
		enTitleScene,	//タイトル
		enGameScene,	//ゲーム
		enLoadScene,	//ロード
		enClearScene,	//クリア
		enBossScene,	//ボス
		enSceneNum		//シーンの数
	};
	~CSceneManager();

	//初期化
	void Init();

	//更新
	void Update();

	void BeforeDead()override;

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

	//マップの取得
	Map* GetMap();

	//フェードアウトが開始したか
	bool GetFadeOut()
	{
		return m_isFadeOut;
	}

	//シーン切り替えが行われたか
	bool GetSceneChange()
	{
		return m_isSceneChange;
	}

	//ゲーム開始時フラグ取得
	bool GetIsStart()
	{
		return m_isStart;
	}

	//ゲーム開始時フラグ設定
	void SetIsStart(bool IsStart)
	{
		m_isStart = IsStart;
	}

private:
	EnSceneState	m_preSceneState= enSceneNum;//シーンのステート（現在のシーンを入れておく用）
	EnSceneState	m_nextSceneState = enSceneNum;//シーンのステート（次のシーンを入れておく用）
	CGameScene*		m_gameScene=nullptr;			//ゲームシーン
	CTitleScene*	m_titleScene = nullptr;			//タイトルシーン
	CClearScene*	m_clearScene = nullptr;			//クリアシーン
	CBossScene*		m_bossScene = nullptr;			//ボスシーン
	CFade*			m_fade;							//フェイド
	bool			m_isSceneChange = false;		//シーン切り替え
	bool			m_isFadeOut = false;			//フェードアウトしたかどうか
	bool			m_isStart=false;				//ゲーム開始時だけのフラグ
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