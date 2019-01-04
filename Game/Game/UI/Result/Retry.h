/*
*	リトライ表示をするクラス
*/

#pragma once

class CRetry : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update() override;

	//描画
	void AfterDraw() override;

	enum EnRetry 
	{
		Continue,	//コンティニュー
		Quit,		//やめる
	};

	//状態を取得
	EnRetry GetState()
	{
		return m_state;
	}

private:
	EnRetry			m_state = Continue;	//状態
	CSprite			m_continue;			//コンティニュー
	CSprite			m_quit;				//やめる
	CSprite			m_cursor;			//カーソル
};