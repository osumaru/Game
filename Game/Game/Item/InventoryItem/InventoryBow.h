/*
*	�C���x���g���ɓ����p�̋|
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryBow : public IInventoryEquip
{
public:
	//������
	void Init() override;

	//�`��
	void Draw() override;
};