/*
*	����I����UI�N���X
*/

#pragma once

class CWeaponSelect : public GameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//����ύX
	void ChangeWeapon();

	//����̎��
	enum EnWeaponType {
		enSword,		//��
		enLargeSword,	//�匕
		enBow,			//�|
		enTwinSword,	//�o��
		enWeaponNum
	};

private:
	Sprite m_weapon[enWeaponNum];			//����
	Texture m_weaponTexture[enWeaponNum];

	Sprite m_crossKey;					//�\���L�[
	Texture m_crossKeyTexture;

	Sprite m_LBButton;					//LB�{�^��
	Texture m_LBButtonTexture;

	Sprite m_RBButton;					//RB�{�^��
	Texture m_RBButtonTexture;

	Vector2 crossKeyPos;				//�\���L�[�̍��W
	Vector2 size;						//�T�C�Y

	int weaponNumber = enSword;			//�ύX���镐��̔ԍ�
	int weaponNumberOld = enSword;		//���ݑI�����Ă��镐��̔ԍ�

	bool	m_selectFlag[enWeaponNum];	//�I����������t���O
};