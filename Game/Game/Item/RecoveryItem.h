/*
*	�񕜃A�C�e���N���X
*/

#pragma once

#include "IItem.h"
#include "GameItem/ItemStatus.h"

class CRecoveryItem : public IItem
{
public:
	//������
	void Init(const CVector3& position);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
private:
	SItemStatus m_status;	//�A�C�e���̃X�e�[�^�X
	bool m_isRePop = false;	//���|�b�v���Ă��邩
};
