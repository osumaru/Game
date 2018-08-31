/*
*	武器選択のUIクラス
*/

#pragma once

class WeaponSelect : public GameObject
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
	enum WeaponType {
		Sword,		//剣
		LargeSword,	//大剣
		Bow,		//弓
		TwinSword,	//双剣
		WeaponNum
	};

private:
	Sprite m_weapon[WeaponNum];			//武器
	Texture m_weaponTexture[WeaponNum];

	Sprite m_crossKey;					//十字キー
	Texture m_crossKeyTexture;

	Sprite m_LBButton;					//LBボタン
	Texture m_LBButtonTexture;

	Sprite m_RBButton;					//RBボタン
	Texture m_RBButtonTexture;

	Vector2 crossKeyPos;				//十字キーの座標
	Vector2 size;						//サイズ

	int weaponNumber = Sword;			//変更する武器の番号
	int weaponNumberOld = Sword;		//現在選択している武器の番号

	bool	m_selectFlag[WeaponNum];	//選択した武器フラグ
};