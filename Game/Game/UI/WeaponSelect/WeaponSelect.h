#include "../../Player/Weapon/WeaponManager.h"
/*
*	武器選択のUIクラス
*/
#pragma once


class CWeaponSelect : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void PostAfterDraw();

	//武器変更
	void ChangeWeapon();


private:
	CSprite		m_weaponChoice;					//選択している武器のスプライト
	CSprite		m_weapon[enWeaponNum];			//武器
	CTexture*	m_weaponTexture[enWeaponNum];	
	CSprite		m_crossKey;						//十字キー
	CTexture*	m_crossKeyTexture;
	CSprite		m_LBButton;						//LBボタン
	CTexture*	m_LBButtonTexture;
	CSprite		m_RBButton;						//RBボタン
	CTexture*	m_RBButtonTexture;
	CVector2	crossKeyPos;					//十字キーの座標
	CVector2	size;							//サイズ
	int			weaponNumber = enWeaponSword;	//変更する武器の番号
};