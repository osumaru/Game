#pragma once
//���Ԃ��v������N���X

class CStopWatch
{
public:

	//�R���X�g���N�^
	CStopWatch();

	//�f�X�g���N�^
	~CStopWatch();

	//�v���J�n
	void Start();

	//�v���I��
	void Stop();

	//�o�ߎ��Ԃ��擾(�P�ʂ͕b)
	double GetElapsedTime() const
	{
		return m_time;
	}

	double GetElapsedTimeMill() const
	{
		return m_millTime;
	}

private:
	LONGLONG m_start;			//�X�^�[�g���̎���
	LONGLONG m_end;				//�I�����̎���
	LONGLONG m_frequency;		//1�b����Ƃ������g��
	double	m_time;				//�o�ߎ���(�P�ʁF�b)
	double	m_millTime;			//�o�ߎ���(�P�ʁF�~���b)
};