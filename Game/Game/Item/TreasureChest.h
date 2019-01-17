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
	std::unique_ptr<IInventoryEquip> m_inventoryEquip;	//�C���x���g���ɓ���鑕��

};