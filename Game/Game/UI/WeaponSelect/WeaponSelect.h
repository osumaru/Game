/*
*	����I����UI�N���X
*/

#pragma once

class WeaponSelect : public GameObject
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
	enum WeaponType {
		Sword,		//��
		LargeSword,	//�匕
		Bow,		//�|
		TwinSword,	//�o��
		WeaponNum
	};

private:
	Sprite m_weapon[WeaponNum];			//����
	Texture m_weaponTexture[WeaponNum];

	Sprite m_crossKey;					//�\���L�[
	Texture m_crossKeyTexture;

	Sprite m_LBButton;					//LB�{�^��
	Texture m_LBButtonTexture;

	Sprite m_RBButton;					//RB�{�^��
	Texture m_RBButtonTexture;

	Vector2 crossKeyPos;				//�\���L�[�̍��W
	Vector2 size;						//�T�C�Y

	int weaponNumber = Sword;			//�ύX���镐��̔ԍ�
	int weaponNumberOld = Sword;		//���ݑI�����Ă��镐��̔ԍ�

	bool	m_selectFlag[WeaponNum];	//�I����������t���O
};