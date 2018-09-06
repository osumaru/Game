#pragma once
//�T�E���h�G���W��
class CSoundSource;
#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//�ő�o�̓`�����l�����B
#include "../Math\Math.h"
#include "../Math/Matrix.h"
#include "../Math\Vector.h"
class CSoundEngine : Uncopyable
{
public:

	//�R���X�g���N�^
	CSoundEngine();

	//�f�X�g���N�^
	~CSoundEngine();

	//������
	void Init();

	//�X�V�֐�
	void Update();
	
	//3D�T�E���h���X�g�ɒǉ�
	void Add3dSound(CSoundSource* sound)
	{
		m_3dSound.push_back(sound);
	}

	//3D�T�E���h���X�g����폜
	void Delete3dSound(CSoundSource* sound)
	{
		auto& it = std::find(m_3dSound.begin(), m_3dSound.end(), sound);
		if (it != m_3dSound.end())
		{
			m_3dSound.erase(it);
		}
	}

	//���X�i�[�̍��W��ݒ�
	void SetListenerPosition(const CVector3& position)
	{
		m_3dListener.Position.x = position.x;
		m_3dListener.Position.y = position.y;
		m_3dListener.Position.z = position.z;
	}

	//���X�i�[�̑O������ݒ�
	void SetListenerFront(const CVector3& front)
	{
		m_3dListener.OrientFront.x = front.x;
		m_3dListener.OrientFront.y = front.y;
		m_3dListener.OrientFront.z = front.z;
	}

	//���X�i�[�̏������ݒ�
	void SetListenerUp(const CVector3& up)
	{
		m_3dListener.OrientTop.x = up.x;
		m_3dListener.OrientTop.y = up.y;
		m_3dListener.OrientTop.z = up.z;
	}

	/*
	�\�[�X�{�C�X���쐬
	format	wave�t�@�C���̃t�H�[�}�b�g
	ret		������\�[�X�{�C�X��Ԃ�
	*/
	IXAudio2SourceVoice* CreateSouceVoice(WAVEFORMATEX* format, bool is3DSound);

	DWORD GetChannelNum() const
	{
		return m_channelNum;
	}

private:
	DWORD					m_channelNum;
	X3DAUDIO_LISTENER		m_3dListener;		//���X�i�[
	X3DAUDIO_HANDLE			m_3dAudioHandle;	//�RD�T�E���h�̃n���h��
	std::list<CSoundSource*> m_3dSound;			//3D�T�E���h�̃��X�g
	IXAudio2*				m_xAudio;			//�I�[�f�B�I
	IXAudio2MasteringVoice* m_masteringVoice;	//�}�X�^�[�{�C�X
};
