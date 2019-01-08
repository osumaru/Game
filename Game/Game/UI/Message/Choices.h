/*
*	選択肢を表示をするクラス
*/

#pragma once

class CChoices : public IGameObject
{
public:
	//初期化
	//select1	1つ目の選択肢
	//select2	2つ目の選択肢
	void Init(wchar_t* select1, wchar_t* select2);

	//更新
	void Update() override;

	//描画
	void AfterDraw() override;

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
	EnSelect		m_state = Yes;		//状態
	CFont			m_yes;				//はい
	CFont			m_no;				//いいえ
	CSprite			m_cursor;			//カーソル
	bool			m_isSelect = false;	//選択肢を選んだか
};