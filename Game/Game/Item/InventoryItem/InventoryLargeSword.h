/*
*	�C���x���g���ɓ����p�̑匕
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryLargeSword : public IInventoryEquip
{
public:
	//������
	void Init(const wchar_t* itemName, const wchar_t* textureFileName) override;

	//�`��
	void Draw() override;
};