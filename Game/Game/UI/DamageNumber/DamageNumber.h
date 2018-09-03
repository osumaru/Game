/*
*	�_���[�W���l�\���N���X
*/

#pragma once


class CPlayer;
class CEnemy;

#include "Number.h"

class CDamegeNumber
{
public:
	//������
	void Init();

	//�_���[�W�v�Z
	//player	�v���C���[�N���X�̃|�C���^
	//enemy		�G�l�~�[�N���X�̃|�C���^

	void DamageCalculation(CPlayer* player, CEnemy* enemy);


private:
	CNumber* m_number[3];	//�����̃X�v���C�g
	Vector2 m_numPos;		//���W
	Vector2 m_numSize;		//�T�C�Y
};