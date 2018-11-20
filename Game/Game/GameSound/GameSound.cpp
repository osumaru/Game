#include "stdafx.h"
#include "GameSound.h"


CGameSound::CGameSound()
{
}


CGameSound::~CGameSound()
{
}


bool CGameSound::Start()
{
	m_backSound[enTownBgm].Init("Assets/sound/BackSound/TownBgm.wav");
	m_backSound[enTownBgm].SetVolume(MASTER_VOLUME);
	m_backSound[enShopBgm].Init("Assets/sound/BackSound//ShopBgm.wav");
	m_backSound[enShopBgm].SetVolume(MASTER_VOLUME);
	return true;
}

void CGameSound::Update()
{

	switch (m_soundState)
	{
	case enWorldBgm:
		m_soundState = enTownBgm;
		m_backSound[enTownBgm].Play(true,true);
		break;
	case enTownBgm:
		if (m_isShop)
		{
			m_backSound[enTownBgm].Stop();;
			m_soundState = enShopBgm;
			m_backSound[enShopBgm].Play(true, true);
		}
		break;
	case enBattleBgm:

		break;
	case enShopBgm:
		if (!m_isShop)
		{
			m_backSound[enShopBgm].Stop();
			m_soundState = enTownBgm;
			m_backSound[enTownBgm].Play(true, false);
			m_backSound[enTownBgm].SetVolume(MASTER_VOLUME);
		}
		break;
	}

	m_backSound[enTownBgm].Update();
}