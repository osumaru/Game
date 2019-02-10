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

	//自身を削除するフラグを設定する
	//deleteFlag	自身を削除するフラグ
	void SetDeleteFlag(bool deleteFlag)
	{
		m_deleteFlag = deleteFlag;
	}

private:
	EnSelect		m_state = No;		//状態
	CSprite			m_yes;				//はい
	CSprite			m_no;				//いいえ
	CSprite			m_cursor;			//カーソル
	CSprite			m_window;			//ウィンドウ
	float			m_timer = 0.0f;		//タイマー
	bool			m_isSelect = false;	//選択肢を選んだか
	bool			m_isAlpha = true;	//透明になっているか
	bool			m_deleteFlag = false;//自身を削除するフラグ
};