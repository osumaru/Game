/*
*	���g���C�\��������N���X
*/

#pragma once

class CRetry : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update() override;

	//�`��
	void AfterDraw() override;

	enum EnRetry 
	{
		Continue,	//�R���e�B�j���[
		Quit,		//��߂�
	};

	//��Ԃ��擾
	EnRetry GetState()
	{
		return m_state;
	}

private:
	EnRetry			m_state = Continue;	//���
	CSprite			m_continue;			//�R���e�B�j���[
	CSprite			m_quit;				//��߂�
	CSprite			m_cursor;			//�J�[�\��
};