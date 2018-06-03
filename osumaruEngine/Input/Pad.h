#pragma once
//�p�b�h�̓��͂��擾����N���X

enum EnPadButton
{
	enButtonUp,
	enButtonDown,
	enButtonLeft,
	enButtonRight,
	enButtonA,
	enButtonB,
	enButtonX,
	enButtonY,
	enButtonSelect,
	enButtonStart,
	enButtonRB,
	enButtonRStickPush,
	enButtonLB,
	enButtonLStickPush,
	enButtonNum,

};

class Pad
{
public:

	//�R���X�g���N�^
	Pad();

	//�f�X�g���N�^
	~Pad();

	//�X�V
	void Update();

	/*
	�{�^���������Ă��邩���ׂ�֐�
	button			������Ă��邩���ׂ����{�^����enum
	*/
	bool IsTriggerButton(EnPadButton button) const
	{
		return m_isPadTrigger[button];
	}

	/*
	�{�^���������Ă��邩���ׂ�֐�
	button			������Ă��邩���ׂ����{�^����enum
	*/
	bool IsPressButton(EnPadButton button) const
	{
		return m_isPadPress[button];
	}

	//���X�e�B�b�N��X���̓��͗ʂ��擾(-1.0����1.0�̊�
	float GetLeftStickX() const
	{
		return m_leftStickX;
	}

	//���X�e�B�b�N��Y���̓��͗ʂ��擾(-1.0����1.0�̊�
	float GetLeftStickY() const
	{
		return m_leftStickY;
	}

	//�E�X�e�B�b�N��X���̓��͗ʂ��擾(-1.0����1.0�̊�
	float GetRightStickX() const
	{
		return m_rightStickX;
	}

	//�E�X�e�B�b�N��Y���̓��͗ʂ��擾(-1.0����1.0�̊�
	float GetRightStickY() const
	{
		return m_rightStickY;
	}

	//�p�b�h�̍��̃g���K�[�̓��͗ʂ��擾(0.0����1.0
	float GetLeftTrigger() const
	{
		return m_leftTrigger;
	}
	//�p�b�h�̉E�̃g���K�[�̓��͗ʂ��擾(0.0����1.0
	float GetRightTrigger() const
	{
		return m_rightTrigger;
	}

private:
	int				m_padNum;						//�p�b�h�̔ԍ�
	float			m_rightStickX;					//�E�X�e�B�b�N��X���̓��͗�
	float			m_rightStickY;					//�E�X�e�B�b�N��Y���̓��͗�
	float			m_leftStickX;					//���X�e�B�b�N��X���̓��͗�
	float			m_leftStickY;					//���X�e�B�b�N��Y���̓��͗�
	float			m_rightTrigger;					//�E�g���K�[�̓��͗�
	float			m_leftTrigger;					//���g���K�[�̓��͗�
	bool			m_isPadPress[enButtonNum];		//�e�{�^����������Ă��邩�H
	bool			m_isPadTrigger[enButtonNum];	//�e�{�^����������Ă��邩�H(�g���K�[)
	XINPUT_STATE	m_state;						//�p�b�h�̓��͏��
};