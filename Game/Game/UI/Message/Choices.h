/*
*	�I������\��������N���X
*/

#pragma once

class CChoices : public IGameObject
{
public:
	//������
	//select1	1�ڂ̑I����
	//select2	2�ڂ̑I����
	void Init(wchar_t* select1, wchar_t* select2);

	//�X�V
	void Update() override;

	//�`��
	void AfterDraw() override;

	enum EnSelect 
	{
		Yes,	//�͂�
		No,		//������
	};

	//��Ԃ��擾
	EnSelect GetState()
	{
		return m_state;
	}

	//�I������I�񂾂�
	bool GetIsSelect()
	{
		return m_isSelect;
	}

private:
	EnSelect		m_state = Yes;		//���
	CFont			m_yes;				//�͂�
	CFont			m_no;				//������
	CSprite			m_cursor;			//�J�[�\��
	bool			m_isSelect = false;	//�I������I�񂾂�
};