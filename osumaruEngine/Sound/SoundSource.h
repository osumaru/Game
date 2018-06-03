#pragma once
#include "WaveFileOpen.h"
#include "SoundEngine.h"

class SoundSource : public GameObject
{
public:
	//�R���X�g���N�^
	SoundSource();

	//�f�X�g���N�^
	~SoundSource();

	/*
	������
	filePath		�ǂݍ��݂���Wave�t�@�C���̃p�X
	*/
	void Init(char* filePath, bool is3DSound = false);

	//�X�V
	void Update()override;

	//���W��ݒ�(3D�T�E���h�̎��Ɏg��
	void SetPosition(Vector3 position)
	{
		m_position = position;
	}

	/*
	�Đ�
	isLoop		���[�v�����邩�Htrue�Ȃ烋�[�v�Afalse�Ȃ烋�[�v���Ȃ�
	*/
	void Play(bool isLoop);

	//�ꎞ��~
	void Stop();

	//�\�[�X�{�C�X���擾
	IXAudio2SourceVoice* GetBody()
	{
		return m_sourceVoice;
	}

	//���W���擾
	Vector3& GetPosition()
	{
		return m_position;
	}

	//�{�����[����ݒ�
	void SetVolume(float volume)
	{
		m_sourceVoice->SetVolume(volume, XAUDIO2_COMMIT_NOW);
	}

	int GetInputChannelNum()
	{
		return m_waveFile.GetFormat()->nChannels;
	}

	X3DAUDIO_DSP_SETTINGS* GetDSPSettings()
	{
		return &m_dspSettings;
	}

	FLOAT32* GetEmitterAzimuths()
	{
		return m_emitterAzimuths;
	}

	FLOAT32* GetCoefficients()
	{
		return m_coefficients;
	}

private:
	Vector3				m_position;			//���W
	FLOAT32					m_coefficients[INPUTCHANNELS * OUTPUTCHANNELS];
	FLOAT32					m_emitterAzimuths[INPUTCHANNELS];
	X3DAUDIO_DSP_SETTINGS	m_dspSettings;
	IXAudio2SourceVoice*	m_sourceVoice;		//�\�[�X�{�C�X
	WaveFileOpen			m_waveFile;			//WAVE�t�@�C���̃f�[�^
	bool					m_isLoop;			//���[�v�t���O
	bool					m_isPlaying;		//�Đ������H
	bool					m_is3DSound;		//3D�T�E���h���H
};