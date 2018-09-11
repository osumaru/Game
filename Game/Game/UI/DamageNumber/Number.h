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
private:
	CSprite		m_number[10];			//�X�v���C�g
	CTexture	m_numberTexture[10];	//�e�N�X�`��
	int			m_num = 0;				//���l��ۑ�����ϐ�
};