/*
*	�����N���X 
*/

#pragma once

class Number : public GameObject
{
public:
	//������
	//Vector2  numPos  ���W
	//Vector2  numSize �T�C�Y
	void Init(Vector2 numPos, Vector2 numSize);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�\�����鐔�l��ݒ�
	//int  num  ���l
	void SetNumber(int num);
private:
	Sprite	m_number[10];			//�X�v���C�g
	Texture m_numberTexture[10];	//�e�N�X�`��
	int		m_num = 0;				//���l��ۑ�����ϐ�
};