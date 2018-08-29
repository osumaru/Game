/*
*	����I����UI�N���X
*/

#pragma once

class WeaponSelect : public GameObject
{
public:
	void Init();

	void Update();

	void Draw();

private:
	Sprite m_crossKey;			//�\���L�[
	Texture m_crossKeyTexture;

	Sprite m_largeSword;		//�匕
	Texture m_largeSwordTexture;

	Sprite m_sword;				//��
	Texture m_swordTexture;

	Sprite m_twinSword;			//�o��
	Texture m_twinSwordTexture;

	Sprite m_bow;				//�|
	Texture m_bowTexture;
};