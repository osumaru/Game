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

	int GetWeapon()
	{
		return weaponNumberOld;
	}

private:
	CSprite		m_weapon[enWeaponNum];			//武器
	CTexture	m_weaponTexture[enWeaponNum];
	CSprite		m_crossKey;						//十字キー
	CTexture	m_crossKeyTexture;
	CSprite		m_LBButton;						//LBボタン
	CTexture	m_LBButtonTexture;
	CSprite		m_RBButton;						//RBボタン
	CTexture	m_RBButtonTexture;
	CVector2	crossKeyPos;					//十字キーの座標
	CVector2	size;							//サイズ
	int			weaponNumber = enSword;			//変更する武器の番号
	int			weaponNumberOld = enSword;		//現在選択している武器の番号
	bool		m_selectFlag[enWeaponNum];		//選択した武器フラグ
};