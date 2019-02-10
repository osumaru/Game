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

	//���g���폜����t���O��ݒ肷��
	//deleteFlag	���g���폜����t���O
	void SetDeleteFlag(bool deleteFlag)
	{
		m_deleteFlag = deleteFlag;
	}

private:
	EnSelect		m_state = No;		//���
	CSprite			m_yes;				//�͂�
	CSprite			m_no;				//������
	CSprite			m_cursor;			//�J�[�\��
	CSprite			m_window;			//�E�B���h�E
	float			m_timer = 0.0f;		//�^�C�}�[
	bool			m_isSelect = false;	//�I������I�񂾂�
	bool			m_isAlpha = true;	//�����ɂȂ��Ă��邩
	bool			m_deleteFlag = false;//���g���폜����t���O
};