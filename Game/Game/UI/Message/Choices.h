/*
*	�I������\��������N���X
*/

#pragma once

class CChoices : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update() override;

	//�`��
	void PostAfterDraw() override;

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
	EnSelect		m_state = No;		//���
	CSprite			m_yes;				//�͂�
	CSprite			m_no;				//������
	CSprite			m_cursor;			//�J�[�\��
	CSprite			m_window;			//�E�B���h�E
	bool			m_isSelect = false;	//�I������I�񂾂�
};