#pragma once
#include "StopWatch.h"
class CFont;
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
	void Init();
	

	//�C���X�^���X���擾
	static CGameTime& GetInstance()
	{
		static CGameTime gametime;
		return gametime;
	}

	//1�t���[���̌o�ߎ��Ԃ��擾 
	float GetDeltaFrameTime() const
	{
		return m_gameDeltaTime;
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

	/*
	���Ԃ��X���[�ɂ���ݒ�
	slowTime	�X���[�ɂȂ��Ă��鎞��
	slowScale	�ǂ̂��炢�X���[�ɂ��邩�̔{��(1.0������
	delayTime	�X���[�ɂȂ�܂ł̒x������
	*/
	void SetSlowDelayTime(float slowTime, float slowScale, float delayTime)
	{
		SetSlow(slowTime, slowScale);
		m_slowDelayTime = delayTime;
	}

	/*
	���Ԃ��X���[�ɂ���ݒ�
	slowTime	�X���[�ɂȂ��Ă���t���[����
	slowScale	�ǂ̂��炢�X���[�ɂ��邩�̔{��(1.0������
	delayTime	�X���[�ɂȂ�܂ł̒x������
	*/
	void SetSlowDelayTime(int slowCount, float slowScale, float delayTime)
	{
		SetSlow(slowCount, slowScale);
		m_slowDelayTime = delayTime;
	}

	/*
	���Ԃ��X���[�ɂ���ݒ�
	slowTime	�X���[�ɂȂ��Ă��鎞��
	slowScale	�ǂ̂��炢�X���[�ɂ��邩�̔{��(1.0������
	delayCount	�X���[�ɂȂ�܂ł̒x������t���[����
	*/
	void SetSlowDelayCount(float slowTime, float slowScale, int delayCount)
	{
		SetSlow(slowTime, slowScale);
		m_slowDelayCount = delayCount;
	}

	/*
	���Ԃ��X���[�ɂ���ݒ�
	slowTime	�X���[�ɂȂ��Ă���t���[����
	slowScale	�ǂ̂��炢�X���[�ɂ��邩�̔{��(1.0������
	delayTime	�X���[�ɂȂ�܂ł̒x������t���[����
	*/
	void SetSlowDelayCount(int slowCount, float slowScale, int delayCount)
	{
		SetSlow(slowCount, slowScale);
		m_slowDelayCount = delayCount;
	}

	//FPS��\��
	void Draw();

	//�X���[����߂����̃t�F�[�h���Ԃ�ݒ�
	void SetFadeOutTime(float fadeOutTime)
	{
		m_fadeOutTime = fadeOutTime;
		m_fadeOutTimeMax = fadeOutTime;
	}

	//�ʏ펞����X���[�ɓ��鎞�̃t�F�[�h���Ԃ�ݒ�
	void SetFadeInTime(float fadeInTime)
	{
		m_fadeInTime = fadeInTime;
		m_fadeInTimeMax = fadeInTime;
	}

private:
	friend class CShakeCamera;
	float		m_slowScale = 0.0f;		//�ǂ̂��炢�X���[�ɂ��Ă��邩�̔{��(1.0������
	float		m_slowTime = 0.0f;		//�X���[�ɂȂ��Ă���Ԃ̎���
	int			m_slowCount = 0;		//�X���[�ɂȂ��Ă���Ԃ̃t���[����
	float		m_gameDeltaTime;		//�Q�[���̒��̎��Ԃł�1�t���[���̌o�ߎ���
	float		m_frameDeltaTime;		//1�t���[���̌o�ߎ���
	float		m_slowDelayTime = 0.0f;	//�X���[�ɂ���܂ł̒x������
	int			m_slowDelayCount = 0;	//�X���[�ɂ���܂ł̃t���[����
	float		m_fadeInTime = 0.0f;	//���ʂ̎��Ԃ���X���[�ɂȂ�܂Ńt�F�[�h������Ԃ̎���
	float		m_fadeInTimeMax = 0.0f;
	float		m_fadeOutTime = 0.0f;	//�X���[���畁�ʂ̎��ԂɂȂ�܂Ńt�F�[�h������Ԃ̎���
	float		m_fadeOutTimeMax = 0.0f;	//�X���[���畁�ʂ̎��ԂɂȂ�܂Ńt�F�[�h������Ԃ̎���
	CFont*		m_font;					//FPS�\�������邽�߂̕���
};

//�Q�[���^�C�}�[���擾
static CGameTime& GameTime()
{
	return CGameTime::GetInstance();
}