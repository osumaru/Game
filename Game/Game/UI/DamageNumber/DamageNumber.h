/*
*	�_���[�W���l�\���N���X
*/

#pragma once


class CPlayer;

#include "Number.h"

class CDamegeNumber
{
public:
	//������
	void Init();

	//�_���[�W�v�Z
	void DamageCalculation();

	//�_���[�W�\�����Z�b�g
	void Reset();

	//���W��ݒ�
	//position	���W
	void SetPosition(CVector2 position)
	{
		m_numPos = position;
	}
private:
	CNumber* m_number[3];	//�����̃X�v���C�g
	CVector2 m_numPos;		//���W
	CVector2 m_numSize;		//�T�C�Y
};