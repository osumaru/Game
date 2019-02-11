#pragma once


class CGameSound : public IGameObject
{
public:
	enum EnSoundState
	{
		enTitleBgm,			//�^�C�g����BGM
		enWorldBgm,			//���[���h�}�b�v�ړ�����BGM
		enTownBgm,			//���ɓ���������BGM
		enBattleBgm,		//�퓬����BGM
		enShopBgm,			//���X��BGM
		enBossBgm,			//�{�X���BGM
		enDeathBgm,			//���SBGM
		enBgmNum			//BGM�̐�
	};

	enum EnSoundFadeState
	{
		enFadeOut,
		enFadeIn,
	};

	CGameSound();
	~CGameSound();
	bool Start();
	void Update();
	void SetIsShop(const bool set)
	{
		m_isShop = set;
	}
	//���y�̐؂�ւ����s���֐�
	void SetGameSound(EnSoundState BgmName)
	{
		m_backSound[m_soundState].m_backSound.Stop();
		m_soundState = BgmName;
		m_backSound[m_soundState].m_backSound.Play(m_backSound[m_soundState].m_isLoop, m_backSound[m_soundState].m_isBegin);
	}
	void GamesoundFadeIn()
	{
		m_isFade = true;
		m_state = EnSoundFadeState::enFadeIn;
	}
	void GamesoundFadeOut()
	{
		m_isFade = true;
		m_state = EnSoundFadeState::enFadeOut;
	}
	//�����ŉ��ʒ������s���֐�
	//�����@�ő剹�ʂ͈̔�
	void SoundLenght();

	void FadeSound();
private:
	struct BackSoundStatus
	{
		CSoundSource	m_backSound;
		float			m_volume = 1.0f;
		bool			m_isLoop = true;
		bool			m_isBegin = true;
		CVector3		m_soundPosition = CVector3::Zero;
		float			m_lenght = 10.0f;
		bool			m_isMapSound = false;
	};
	BackSoundStatus		m_backSound[7];
	//CSoundSource		m_backSound[7];
    EnSoundState		m_soundState = enBossBgm;
	EnSoundState		m_nextSoundState = enWorldBgm;
	const float			MASTER_VOLUME = 1.0f;			//BGM�̉���
	float				m_bgmVolume = 0.0f;
	CVector3			m_soundPosition = CVector3::Zero;
	

	bool				m_isMenu;					
	bool				m_isShop = false;
	bool				m_isTown;
	float				m_volumeDownLen = 20.0f;		//���ȏ㗣�ꂽ�特��������
	float				m_fadeTime = 0.0f;
	bool				m_isFade = false;
	EnSoundFadeState	m_state = EnSoundFadeState::enFadeIn;
	const float			FADE_IN_TIME = 2.0f;
	const float			FADE_OUT_TIME = 2.0f;
};

