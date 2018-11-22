#pragma once
class CGameSound: public IGameObject
{
public:
	CGameSound();
	~CGameSound();
	bool Start();
	void Update();
	void SetIsShop(const bool set)
	{
		m_isShop = set;
	}

private:
	enum EnSoundState
	{
		enWorldBgm,			//ワールドマップ移動中のBGM
		enTownBgm,			//町に入った時のBGM
		enBattleBgm,		//戦闘中のBGM
		enShopBgm,			//お店のBGM
		enBgmNum			//BGMの数
	};
	CSoundSource		m_backSound[4];
	EnSoundState		m_soundState = enWorldBgm;
	const float			MENU_SOUND_VOLUME = 0.5f;
	const float			MASTER_VOLUME = 0.3f;			//BGMの音量
	const float			SHOP_MASTER_VOLUME = 0.1f;		//ショップのBGMの音量
	bool				m_isMenu;					
	bool				m_isShop = false;
	bool				m_isTown;
};

