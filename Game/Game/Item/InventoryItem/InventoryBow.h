/*
*	�C���x���g���ɓ����p�̋|
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryBow : public IInventoryEquip
{
public:
	//������
	void Init(const wchar_t* itemName, const wchar_t* textureFileName) override;

	//�`��
	void Draw() override;
};