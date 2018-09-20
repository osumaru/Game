/*
*	����I����UI�N���X
*/

#pragma once


class CWeaponSelect : public IGameObject
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

	int GetWeapon()
	{
		return weaponNumberOld;
	}

private:
	CSprite		m_weapon[enWeaponNum];			//����
	CTexture	m_weaponTexture[enWeaponNum];
	CSprite		m_crossKey;						//�\���L�[
	CTexture	m_crossKeyTexture;
	CSprite		m_LBButton;						//LB�{�^��
	CTexture	m_LBButtonTexture;
	CSprite		m_RBButton;						//RB�{�^��
	CTexture	m_RBButtonTexture;
	CVector2	crossKeyPos;					//�\���L�[�̍��W
	CVector2	size;							//�T�C�Y
	int			weaponNumber = enSword;			//�ύX���镐��̔ԍ�
	int			weaponNumberOld = enSword;		//���ݑI�����Ă��镐��̔ԍ�
	bool		m_selectFlag[enWeaponNum];		//�I����������t���O
};