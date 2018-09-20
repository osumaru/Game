/*
*	�����N���X 
*/

#pragma once

class CNumber : public IGameObject
{
public:
	//������
	//Vector2  numPos  ���W
	//Vector2  numSize �T�C�Y
	void Init(CVector2 numPos, CVector2 numSize);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�\�����鐔�l��ݒ�
	//int  num  ���l
	void SetNumber(int num);

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