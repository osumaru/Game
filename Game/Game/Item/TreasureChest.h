/*
*	�����A�C�e���N���X
*/

#pragma once

#include "IItem.h"
#include "../Player/Weapon.h"

class CTreasureChest : public IItem
{
public:
	//������
	//position		���W
	void Init(CVector3 position);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
private:
	CWeapon::SWeaponStatus m_weaponStatus;	//����̃X�e�[�^�X
};