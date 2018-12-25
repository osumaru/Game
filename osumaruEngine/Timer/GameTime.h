#pragma once
#include "StopWatch.h"

class CGameTime
{
	//�R���X�g���N�^
	CGameTime() :
		m_frameDeltaTime(1.0f / 60.0f)
	{
	}

	//�f�X�g���N�^
	~CGameTime()
	{

	}
public:

	//�C���X�^���X���擾
	static CGameTime& GetInstance()
	{
		static CGameTime gametime;
		return gametime;
	}

	//1�t���[���̌o�ߎ��Ԃ��擾 
	float GetDeltaFrameTime() const
	{
		return m_frameDeltaTime;
	}


	void Update(CStopWatch& sw);

	/*
	���Ԃ��X���[�ɂ���ݒ�
	slowTime	�X���[�ɂȂ��Ă��鎞��
	slowScale	�ǂ̂��炢�X���[�ɂ��邩�̔{��(1.0������
	*/
	void SetSlow(float slowTime, float slowScale)
	{
		m_slowTime = slowTime;
		m_slowScale = slowScale;
	}

	/*
���Ԃ��X���[�ɂ���ݒ�
slowTime	�X���[�ɂȂ��Ă���t���[����
slowScale	�ǂ̂��炢�X���[�ɂ��邩�̔{��(1.0������
*/
	void SetSlow(int slowCount, float slowScale)
	{
		m_slowCount = slowCount;
		m_slowScale = slowScale;
	}

private:
	float		m_slowScale = 0.0f;		//�ǂ̂��炢�X���[�ɂ��Ă��邩�̔{��(1.0������
	float		m_slowTime = 0.0f;		//�X���[�ɂȂ��Ă���Ԃ̎���
	int			m_slowCount = 0;
	float		m_frameDeltaTime;		//1�t���[���̌o�ߎ���
};

//�Q�[���^�C�}�[���擾
static CGameTime& GameTime()
{
	return CGameTime::GetInstance();
}