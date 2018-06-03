#pragma once
class WaveFileOpen
{
public:
	//�R���X�g���N�^
	WaveFileOpen();

	//�f�X�g���N�^
	~WaveFileOpen();

	/*
	�t�@�C�����J���ēǂݍ���
	fileName	�J��WAVE�t�@�C���̃p�X
	*/
	void Open(char* fileName);

	//�t�H�[�}�b�g���擾
	WAVEFORMATEX* GetFormat()
	{
		return m_format;
	}

	//�f�[�^�T�C�X���擾
	DWORD GetSize()
	{
		return m_size;
	}

	//�ǂݍ��ݗp�̃o�b�t�@���擾
	char* GetSoundData()
	{
		return m_readMemory.get();
	}

private:

	void Read();

private:
	HMMIO							m_hmmio;			//WAVE�t�@�C���̃n���h��
	MMCKINFO						m_riffChunk;		//��Ԑe�̃`�����N
	MMCKINFO						m_dataChunk;		//�g�`�f�[�^�����`�����N
	DWORD							m_size;				//�f�[�^�̃T�C�Y
	std::unique_ptr<char[]>			m_readMemory;		//�f�[�^��ǂݍ��ޗp�̃o�b�t�@
	WAVEFORMATEX*					m_format;			//WAVE�t�@�C���̃t�H�[�}�b�g
};