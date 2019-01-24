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
	m_backSound[enTitleBgm].Init("Assets/sound/BackSound/TitleBgm.wav");
	m_backSound[enTitleBgm].SetVolume(MASTER_VOLUME);
	m_backSound[enTownBgm].Init("Assets/sound/BackSound/TownBgm.wav");
	m_backSound[enTownBgm].SetVolume(MASTER_VOLUME);
	m_backSound[enShopBgm].Init("Assets/sound/BackSound//ShopBgm.wav");
	m_backSound[enShopBgm].SetVolume(SHOP_MASTER_VOLUME);
	m_backSound[enWorldBgm].Init("Assets/sound/BackSound//FieldBgm.wav");
	m_backSound[enWorldBgm].SetVolume(MASTER_VOLUME);
	//m_backSound[enBossBgm].Init("Assets/sound/BackSound//BossBgm.wav");
	//m_backSound[enBossBgm].SetVolume(MASTER_VOLUME);
	m_backSound[enTitleBgm].Play(true,true);
	return true;
}

void CGameSound::Update()
{

	switch (m_soundState)
	{
	case enTitleBgm:

		break;
	case enWorldBgm:
		//m_soundState = enTownBgm;
		//m_backSound[enTownBgm].Play(true,true);
		if (m_isShop)
		{
			m_backSound[enWorldBgm].Stop();;
			m_soundState = enShopBgm;
			m_backSound[enShopBgm].Play(true, true);
		}
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
			m_soundState = enWorldBgm;
			m_backSound[enWorldBgm].Play(true, false);
			m_backSound[enWorldBgm].SetVolume(MASTER_VOLUME);
		}
		break;

	case enBossBgm:

		break;
	}

	m_backSound[enTownBgm].Update();
}