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

	//�X�V
	void Update() {};

	//�`��
	void Draw() override;

	//�A�C�e�����g��
	bool Use() override;

private:
	int m_recoveryValue = 30;	//�񕜒l
};