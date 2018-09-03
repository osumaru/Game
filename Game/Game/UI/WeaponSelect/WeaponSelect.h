/*
*	武器選択のUIクラス
*/

#pragma once

class CWeaponSelect : public GameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

	//武器変更
	void ChangeWeapon();

	//武器の種類
	enum EnWeaponType {
		enSword,		//剣
		enLargeSword,	//大剣
		enBow,			//弓
		enTwinSword,	//双剣
		enWeaponNum
	};

private:
	Sprite m_weapon[enWeaponNum];			//武器
	Texture m_weaponTexture[enWeaponNum];

	Sprite m_crossKey;					//十字キー
	Texture m_crossKeyTexture;

	Sprite m_LBButton;					//LBボタン
	Texture m_LBButtonTexture;

	Sprite m_RBButton;					//RBボタン
	Texture m_RBButtonTexture;

	Vector2 crossKeyPos;				//十字キーの座標
	Vector2 size;						//サイズ

	int weaponNumber = enSword;			//変更する武器の番号
	int weaponNumberOld = enSword;		//現在選択している武器の番号

	bool	m_selectFlag[enWeaponNum];	//選択した武器フラグ
};