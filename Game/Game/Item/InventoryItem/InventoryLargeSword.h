/*
*	�C���x���g���ɓ����p�̑匕
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryLargeSword : public IInventoryEquip
{
public:
	//������
	void Init() override;

	//�`��
	void Draw() override;
};