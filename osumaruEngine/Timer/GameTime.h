#pragma once

class GameTime
{
	//�R���X�g���N�^
	GameTime() :
		m_frameDeltaTime(1.0f / 60.0f)
	{
	}

	//�f�X�g���N�^
	~GameTime()
	{

	}
public:
	//�C���X�^���X���擾
	static GameTime& GetInstance()
	{
		static GameTime gametime;
		return gametime;
	}

	//1�t���[���̌o�ߎ��Ԃ�ݒ�
	void SetFrameDeltaTime(float frameDeltaTime)
	{
		m_frameDeltaTime = min(1.0f / 10.0f, frameDeltaTime);
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
static GameTime& GetGameTime()
{
	return GameTime::GetInstance();
}