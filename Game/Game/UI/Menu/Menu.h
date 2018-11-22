#pragma once
#include "../../Player/Player.h"

class CItemInventory;
class CEquipInventory;

class CMenu : public IGameObject
{
public:
	CMenu();
	~CMenu();

	void Init();
	void Update();

	void BeforeDead()override;

	void AfterDraw();
	//ステータスを計算する関数
	void StatusMath();			
	//スレイヤーのステータスの入力を行う関数
	void PlayerStatusInput();	
	//キーの入力による処理を行う関数
	void KeyInputMenu();
	//プレイヤーのステータスが変化した場合に再度数値を書き換える処理
	void StatusConversion();

private:
	enum EnMenuState
	{
		enMiniMap,
		enItems,
		enWeapons,
		enSaveGame,
		enExsitGame,
		enNoneMenu,
		num,
	};

	CSprite				m_menu;					//メニュー画面のスプライト
	CTexture			m_Texture;				//メニュー画面のテクスチャ

	CSprite				m_selectSprite;						//メニュー画面の羽ペンアイコンのスプライト
	CTexture			m_selectTexture;				//メニュー画面の羽ペンアイコンテクスチャ
	CVector2			m_selectPosition = CVector2::Zero;
	CVector2			m_selectScale = { 70.0f,70.0f };
	const CVector2		SELECT_TEX_POS = { -270.0f,320.0f };

	const float			UI_POSITION_Y_UP_LIMIT = 320.0f;
	const float			UI_POSITION_Y_DOWN_LIMIT = -280.0f;
	const float			UI_OFFSET_Y = 150.0f;
	static const int	NUMBER_LINE = 7;			//行の要素数
	static const int	NUMBER_COLUMN = 4;			//列の要素数
	CSprite	*			m_number[NUMBER_LINE][NUMBER_COLUMN];				//プレイヤーのステータスのスプライト(数字)
	CTexture*			m_numberTexture[NUMBER_LINE][NUMBER_COLUMN];		//プレイヤーのステータスのテクスチャ(数字)

	CVector2			m_numberPos = { 500.0,220.0f };//CVector2::Zero;
	int					m_PlayerStatus[7];			//プレイヤーのステータスを持つメンバ変数
	bool				m_draw = false;				//描画を行うかの判定をする変数。
	

	EnMenuState			m_menuState = enNoneMenu;
	int					m_stateNum = 0;

	CItemInventory*		m_itemInventory = nullptr;				//アイテムインベントリ
	CEquipInventory*	m_equipInventory = nullptr;				//装備インベントリ
};

