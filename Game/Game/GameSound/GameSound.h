#pragma once


class CGameSound : public IGameObject
{
public:
	enum EnSoundState
	{
		enTitleBgm,			//タイトルのBGM
		enWorldBgm,			//ワールドマップ移動中のBGM
		enTownBgm,			//町に入った時のBGM
		enBattleBgm,		//戦闘中のBGM
		enShopBgm,			//お店のBGM
		enBossBgm,			//ボス戦のBGM
		enDeathBgm,			//死亡BGM
		enBgmNum			//BGMの数
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
	//音楽の切り替えを行う関数
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
	//距離で音量調整を行う関数
	//引数　最大音量の範囲
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
	const float			MASTER_VOLUME = 1.0f;			//BGMの音量
	float				m_bgmVolume = 0.0f;
	CVector3			m_soundPosition = CVector3::Zero;
	

	bool				m_isMenu;					
	bool				m_isShop = false;
	bool				m_isTown;
	float				m_volumeDownLen = 20.0f;		//一定以上離れたら音を下げる
	float				m_fadeTime = 0.0f;
	bool				m_isFade = false;
	EnSoundFadeState	m_state = EnSoundFadeState::enFadeIn;
	const float			FADE_IN_TIME = 2.0f;
	const float			FADE_OUT_TIME = 2.0f;
};

