/*
*	�C���x���g���ɓ����p�̌�
*/

#pragma once

#include "IInventoryEquip.h"

class CInventorySword : public IInventoryEquip
{
public:
	//������
	void Init() override;

	//�`��
	void Draw() override;
};