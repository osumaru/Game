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
	void Set3DSoundPosition(const CVector3 pos)
	{
		m_3dSoundPosition = pos;
		m_backSound[enBossBgm].SetPosition(m_3dSoundPosition);
	}
	//���y�̐؂�ւ����s���֐�
	void SetGameSound(EnSoundState BgmName,bool begin = true)
	{
		m_backSound[m_soundState].Stop();
		m_soundState = BgmName;
		m_backSound[m_soundState].Play(true, begin);
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

	void FadeSound();
private:
	CSoundSource		m_backSound[6];
    EnSoundState		m_soundState = enBossBgm;
	EnSoundState		m_nextSoundState = enWorldBgm;
	const float			MASTER_VOLUME = 1.0f;			//BGM�̉���
	float				m_bgmVolume = 0.0f;
	CVector3			m_3dSoundPosition = CVector3::Zero;
	bool				m_isMenu;					
	bool				m_isShop = false;
	bool				m_isTown;

	float				m_fadeTime = 0.0f;
	bool				m_isFade = false;
	EnSoundFadeState	m_state = EnSoundFadeState::enFadeIn;
	const float			FADE_IN_TIME = 2.0f;
	const float			FADE_OUT_TIME = 2.0f;
};

