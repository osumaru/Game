/*
*	�C���x���g���ɓ����p�̑匕
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryLargeSword : public IInventoryEquip
{
public:
	//������
	//itemName			�A�C�e���̖��O
	//textureFilePath	�e�N�X�`���̃t�@�C���p�X
	void Init(const wchar_t* itemName, const wchar_t* textureFilePath) override;

	//�`��
	void Draw() override;
};