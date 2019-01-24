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
		enBgmNum			//BGMの数
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
	//音楽の切り替えを行う関数
	void SetGameSound(EnSoundState BgmName)
	{
		m_backSound[m_soundState].Stop();
		m_soundState = BgmName;
		m_backSound[m_soundState].Play(true, true);
	}

private:
	CSoundSource		m_backSound[5];
    EnSoundState		m_soundState = enWorldBgm;
	const float			MENU_SOUND_VOLUME = 0.5f;
	const float			MASTER_VOLUME = 0.3f;			//BGMの音量
	const float			SHOP_MASTER_VOLUME = 0.1f;		//ショップのBGMの音量
	CVector3			m_3dSoundPosition = CVector3::Zero;
	bool				m_isMenu;					
	bool				m_isShop = false;
	bool				m_isTown;
};

