/*
*	�_���[�W���l�\���N���X
*/

#pragma once


class CNumber;

class CDamegeNumber
{
public:
	//������
	void Init();

	//�_���[�W�v�Z
	//dmg	�󂯂��_���[�W
	void DamageCalculation(int dmg);

	//���W��ݒ�
	//position	���W
	void SetPosition(const CVector2& position)
	{
		m_numPos = position;
	}

	enum EnDigit {
		enDigit_One,		//��̈�
		enDigit_Ten,		//�\�̈�
		enDigit_Hundred,	//�S�̈�
		enDigit_Num			//�ʂ̐�
	};

private:
	CNumber* m_number[EnDigit::enDigit_Num];	//�����̃X�v���C�g
	CVector2 m_numPos;							//���W
	CVector2 m_numSize;							//�T�C�Y
};