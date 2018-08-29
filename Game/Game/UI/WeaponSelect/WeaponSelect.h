/*
*	武器選択のUIクラス
*/

#pragma once

class WeaponSelect : public GameObject
{
public:
	void Init();

	void Update();

	void Draw();

private:
	Sprite m_crossKey;			//十字キー
	Texture m_crossKeyTexture;

	Sprite m_largeSword;		//大剣
	Texture m_largeSwordTexture;

	Sprite m_sword;				//剣
	Texture m_swordTexture;

	Sprite m_twinSword;			//双剣
	Texture m_twinSwordTexture;

	Sprite m_bow;				//弓
	Texture m_bowTexture;
};