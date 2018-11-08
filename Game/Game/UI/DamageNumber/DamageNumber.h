/*
*	�_���[�W���l�\���N���X
*/

#pragma once

#include "Number.h"

class CDamageNumber : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update() override;

	//�`��
	void AfterDraw() override;

	//�_���[�W�v�Z
	//dmg	�󂯂��_���[�W
	void DamageCalculation(int dmg);

	//���W��ݒ�
	//position	���W
	void SetPosition(const CVector2& position);

	enum EnDigit {
		enDigit_One,		//��̈�
		enDigit_Ten,		//�\�̈�
		enDigit_Hundred,	//�S�̈�
		enDigit_Num			//�ʂ̐�
	};

private:
	CNumber  m_number[EnDigit::enDigit_Num];	//�����̃X�v���C�g
	CVector2 m_numPos;							//���W
	CVector2 m_numSize;							//�T�C�Y
	float    m_timer = 0.0f;					//�^�C�}�[
	float    m_alphaTime = 0.0f;				//�A���t�@�l���v�Z���邽�߂̎���
	const float m_drawTime = 1.0f;				//�`�悵�Ă��鎞��
};