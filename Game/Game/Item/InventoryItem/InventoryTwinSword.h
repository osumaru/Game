/*
*	�C���x���g���ɓ����p�̑o��
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryTwinSword : public IInventoryEquip
{
public:
	//������
	void Init() override;

	//�`��
	void Draw() override;
};