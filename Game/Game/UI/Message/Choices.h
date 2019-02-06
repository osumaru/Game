/*
*	選択肢を表示をするクラス
*/

#pragma once

class CChoices : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update() override;

	//描画
	void PostAfterDraw() override;

	enum EnSelect 
	{
		Yes,	//はい
		No,		//いいえ
	};

	//状態を取得
	EnSelect GetState()
	{
		return m_state;
	}

	//選択肢を選んだか
	bool GetIsSelect()
	{
		return m_isSelect;
	}

private:
	EnSelect		m_state = No;		//状態
	CSprite			m_yes;				//はい
	CSprite			m_no;				//いいえ
	CSprite			m_cursor;			//カーソル
	CSprite			m_window;			//ウィンドウ
	bool			m_isSelect = false;	//選択肢を選んだか
};