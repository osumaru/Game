/*
*	�񕜃A�C�e���N���X
*/

#pragma once

#include "IItem.h"
#include "InventoryItem/IInventoryItem.h"

class CRecoveryItem : public IItem
{
public:
	//������
	void Init();

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�|�b�v������
	//position	���W
	void Pop(CVector3 position);
};
