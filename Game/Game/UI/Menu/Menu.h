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
	void StatusMath();
	void PlayerStatusInput();

private:
	CSprite			m_menu;					//メニュー画面のスプライト
	CTexture		m_Texture;				//メニュー画面のテクスチャ
	CSprite	*		m_number[7][4];			//プレイヤーのステータスのスプライト(数字)
	CTexture*		m_numberTexture[7][4];	//プレイヤーのステータスのテクスチャ(数字)
	CVector2		m_numberPos = { 500.0,220.0f };//CVector2::Zero;
	int				m_PlayerStatus[7];			//プレイヤーのステータスを持つメンバ変数
	bool			m_Draw = false;				//描画を行うかの判定をする変数。

};

