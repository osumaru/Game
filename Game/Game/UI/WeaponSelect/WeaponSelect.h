#include "../../Player/Weapon/WeaponManager.h"
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
	void PostAfterDraw();

	//����ύX
	void ChangeWeapon();


private:
	CSprite		m_weaponChoice;					//�I�����Ă��镐��̃X�v���C�g
	CSprite		m_weapon[enWeaponNum];			//����
	CTexture*	m_weaponTexture[enWeaponNum];	
	CSprite		m_crossKey;						//�\���L�[
	CTexture*	m_crossKeyTexture;
	CSprite		m_LBButton;						//LB�{�^��
	CTexture*	m_LBButtonTexture;
	CSprite		m_RBButton;						//RB�{�^��
	CTexture*	m_RBButtonTexture;
	CVector2	crossKeyPos;					//�\���L�[�̍��W
	CVector2	size;							//�T�C�Y
	int			weaponNumber = enWeaponSword;	//�ύX���镐��̔ԍ�
};