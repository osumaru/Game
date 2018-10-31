#pragma once
#include "../../Player/Player.h"

class CMenu : public IGameObject
{
public:
	CMenu();
	~CMenu();

	void Init();
	void Update();

	void AfterDraw();
	//ステータスを計算する関数
	void StatusMath();			
	//スレイヤーのステータスの入力を行う関数
	void PlayerStatusInput();	
	//キーの入力による処理を行う関数
	void KeyInputMenu();

private:
	enum EnMenuState
	{
		enMiniMap,
		enItems,
		enWeapons,
		enSaveGame,
		enExsitGame,
		num,
	};

	CSprite			m_menu;					//メニュー画面のスプライト
	CTexture		m_Texture;				//メニュー画面のテクスチャ

	CSprite			m_menuUI;						//メニュー画面の羽ペンアイコンのスプライト
	CTexture		m_menuUITexture;				//メニュー画面の羽ペンアイコンテクスチャ
	CVector2		m_menuUIPosition = { -270.0f,320.0f };
	CVector2		m_menuUIScale = { 70.0f,70.0f };
	const float		UI_POSITION_Y_UP_LIMIT = 320.0f;
	const float		UI_POSITION_Y_DOWN_LIMIT = -280.0f;
	const float		UI_OFFSET_Y = 150.0f;

	const short int NUMBER_LINE = 7;			//行の要素数
	const short int NUMBER_COLUMN = 4;			//列の要素数
	CSprite	*		m_number[7][4];				//プレイヤーのステータスのスプライト(数字)
	CTexture*		m_numberTexture[7][4];		//プレイヤーのステータスのテクスチャ(数字)

	CVector2		m_numberPos = { 500.0,220.0f };//CVector2::Zero;
	int				m_PlayerStatus[7];			//プレイヤーのステータスを持つメンバ変数
	bool			m_Draw = false;				//描画を行うかの判定をする変数。

	EnMenuState		m_MenuState = enMiniMap;
	int				m_StateNum = 0;
};

