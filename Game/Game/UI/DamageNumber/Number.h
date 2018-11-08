/*
*	�����N���X 
*/

#pragma once

class CNumber
{
public:
	//������
	//numPos  ���W
	//numSize �T�C�Y
	void Init(CVector2 numPos, CVector2 numSize);

	//�`��
	void Draw();

	//�\�����鐔�l��ݒ�
	//int  num  ���l
	void SetNumber(int num)
	{
		m_num = num;
	}

	//���W��ݒ�
	//pos	���W
	void SetPosition(CVector2 pos)
	{
		m_number[m_num].SetPosition(pos);
	}

	//Z�l��ݒ�
	//depth		Z�l
	void SetDepthValue(float depth)
	{
		m_number[m_num].SetDepthValue(depth);
	}

	//�A���t�@�l��ݒ�
	//alpha		�A���t�@�l
	void SetAlpha(float alpha)
	{
		m_number[m_num].SetAlpha(alpha);
	}

	//�`�悷�邩�ǂ�����ݒ�
	void SetIsDraw(bool isDraw)
	{
		m_number[m_num].SetIsDraw(isDraw);
	}

	//�`�悷�邩�̔�����擾
	bool GetIsDraw()
	{
		return m_number[m_num].IsDraw();
	}

	enum EnNumber {
		enNumber_Zero,	//0
		enNumber_One,	//1
		enNumber_Two,	//2
		enNumber_Three,	//3
		enNumber_Four,	//4
		enNumber_Five,	//5
		enNumber_Six,	//6
		enNumber_Seven,	//7
		enNumber_Eight,	//8
		enNumber_Nine,	//9
		enNumber_Num	//�����̐�
	};

private:
	CSprite		m_number[EnNumber::enNumber_Num];			//�X�v���C�g
	CTexture	m_numberTexture[EnNumber::enNumber_Num];	//�e�N�X�`��
	int			m_num = 0;									//���l��ۑ�����ϐ�
};