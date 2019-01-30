/*
*	武器選択のUIクラス
*/
#pragma once

#include "../../Player/Weapon/WeaponManager.h"

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
	CVector2	crossKeyPos;					//十字キーの座標
	CVector2	size;							//サイズ
	int			weaponNumber = enWeaponSword;	//変更する武器の番号
};