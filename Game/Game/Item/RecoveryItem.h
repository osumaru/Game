/*
*	�񕜃A�C�e���N���X
*/

#pragma once

#include "IItem.h"

class CRecoveryItem : public IItem
{
public:
	//������
	void Init();

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�A�C�e�����g��
	void Use() override;

	//�|�b�v������
	//position	���W
	void Pop(CVector3 position);

private:
	int m_recoveryValue = 30;	//�񕜒l
};
