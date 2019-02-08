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
	m_bgmVolume = MASTER_VOLUME;
	m_backSound[enTitleBgm].Init("Assets/sound/BackSound/TitleBgm.wav");
	m_backSound[enTitleBgm].SetVolume(m_bgmVolume);
	m_backSound[enTownBgm].Init("Assets/sound/BackSound/TownBgm.wav");
	m_backSound[enTownBgm].SetVolume(m_bgmVolume);
	m_backSound[enShopBgm].Init("Assets/sound/BackSound/ShopBgm.wav");
	m_backSound[enShopBgm].SetVolume(m_bgmVolume);
	m_backSound[enWorldBgm].Init("Assets/sound/BackSound/FieldBgm.wav");
	m_backSound[enWorldBgm].SetVolume(m_bgmVolume);
	m_backSound[enBossBgm].Init("Assets/sound/BackSound/BossBgm.wav");
	m_backSound[enBossBgm].SetVolume(m_bgmVolume);

	m_backSound[m_soundState].Play(true,true);
	return true;
}

void CGameSound::Update()
{

	switch (m_soundState)
	{
	case enTitleBgm:

		break;
	case enWorldBgm:
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
	/*	if (!m_isShop)
		{
			m_backSound[enShopBgm].Stop();
			m_soundState = enWorldBgm;
			m_backSound[enWorldBgm].Play(true, false);
			m_backSound[enWorldBgm].SetVolume(MASTER_VOLUME);
		}*/
		break;

	case enBossBgm:

		break;
	}
	FadeSound();
}

void CGameSound::FadeSound()
{
	if (!m_isFade) { return; }

	switch (m_state)
	{
	case	enFadeOut:
		m_fadeTime += GameTime().GetDeltaFrameTime();
		if (m_fadeTime < FADE_OUT_TIME)
		{
			m_bgmVolume = (min((m_fadeTime / FADE_OUT_TIME), 1.0f));
		}
		else
		{
			m_isFade = false;
			m_fadeTime = 0;
			m_bgmVolume = 1.0f;
		}

		break;

	case enFadeIn:
		m_fadeTime += GameTime().GetDeltaFrameTime();
		if (m_fadeTime < FADE_IN_TIME)
		{
			m_bgmVolume = max((1.0f - (m_fadeTime / FADE_IN_TIME)), 0.0f);
		}
		else
		{
			m_isFade = false;
			m_fadeTime = 0.0f;
			m_bgmVolume = 0.0f;

		}
		break;
	}
	
	m_backSound[m_soundState].SetVolume(m_bgmVolume);
}