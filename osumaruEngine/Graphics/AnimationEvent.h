#pragma once

/*
�A�j���[�V�����C�x���g
*/
class CAnimationEvent
{
public:
	CAnimationEvent() :
		m_isInvoked(false),
		m_invokeTime(0.0f),
		m_eventName()
	{

	}
	//�C�x���g�������Ԃ��擾
	float GetInvokeTime() const
	{
		return m_invokeTime;
	}

	//�C�x���g�����擾
	const wchar_t* GetEventName() const
	{
		return m_eventName;
	}

	//�C�x���g����ݒ�
	void SetEventName(wchar_t* eventName)
	{
		m_eventName = eventName;
	}

	//�C�x���g�������Ԃ�ݒ�
	void SetInvokeTime(float time)
	{
		m_invokeTime = time;
	}

	//�C�x���g�������ς݂�����
	bool IsInvoked() const
	{
		return m_isInvoked;
	}

	//�C�x���g�������ς݂̃t���O��ݒ肷��
	void SetInvokedFlg(bool flg)
	{
		m_isInvoked = flg;
	}
private:
	bool		m_isInvoked;	//�C�x���g�����ς݁H
	float		m_invokeTime;	//�C�x���g��������
	wchar_t*	m_eventName;	//�C�x���g��
};