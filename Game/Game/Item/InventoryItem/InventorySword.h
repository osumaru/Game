/*
*	�C���x���g���ɓ����p�̌�
*/

#pragma once

#include "IInventoryEquip.h"

class CInventorySword : public IInventoryEquip
{
public:
	//������
	//itemName			�A�C�e���̖��O
	//textureFilePath	�e�N�X�`���̃t�@�C���p�X
	void Init(const wchar_t* itemName, const wchar_t* textureFilePath) override;

	//�`��
	void Draw() override;
};