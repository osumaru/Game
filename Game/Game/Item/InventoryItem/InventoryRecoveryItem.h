/*
*	�C���x���g���ɓ����񕜃A�C�e���N���X
*/

#pragma once

#include "IInventoryItem.h"

class CInventoryRecoveryItem : public IInventoryItem
{
public:
	//������
	void Init() override;

	//�`��
	void Draw() override;

	//�A�C�e�����g��
	bool Use() override;

	void TexUpdate() override;

private:
	float m_recoveryValue = 30.0f;	//�񕜒l
};