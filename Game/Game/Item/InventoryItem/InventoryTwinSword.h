/*
*	�C���x���g���ɓ����p�̑o��
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryTwinSword : public IInventoryEquip
{
public:
	//������
	void Init(const wchar_t* itemName, const wchar_t* textureFileName) override;

	//�`��
	void Draw() override;
};