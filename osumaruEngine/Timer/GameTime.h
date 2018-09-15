#pragma once
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

	//1�t���[���̌o�ߎ��Ԃ�ݒ�
	void SetFrameDeltaTime(float frameDeltaTime)
	{
		m_frameDeltaTime =  min(1.0f / 10.0f, frameDeltaTime);
	}

	//1�t���[���̌o�ߎ��Ԃ��擾 
	float GetDeltaFrameTime() const
	{
		return m_frameDeltaTime;
	}

private:
	float m_frameDeltaTime;		//1�t���[���̌o�ߎ���

};

//�Q�[���^�C�}�[���擾
static CGameTime& GameTime()
{
	return CGameTime::GetInstance();
}