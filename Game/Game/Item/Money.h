/*
*	�����̃A�C�e���N���X
*/

#pragma once

#include "IItem.h"

class CMoney : public IItem
{
public:
	//������
	//gold	�����̒l
	void Init(const CVector3& position, const int gold);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

private:
	int m_gold = 0;	//�����̒l
};