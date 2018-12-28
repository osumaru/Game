/*
*	�����A�C�e���N���X
*/

#pragma once

#include "IItem.h"
#include "InventoryItem/IInventoryEquip.h"

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

	//����̃X�e�[�^�X�����߂�
	void DesideWeaponStatus();

private:
	//����̊�{�U����
	const struct SBasicWeaponStatus 
	{
		int basicAttack = 100;		//��{�U����
		int swordAttack = 50;		//���̍U����
		int longSwordAttack = 70;	//�匕�̍U����
		int arrowAttack = 20;		//�|�̍U����
		int twinSwordAttack = 30;	//�o���̍U����
	};

	std::unique_ptr<IInventoryEquip> m_inventoryEquip;
};