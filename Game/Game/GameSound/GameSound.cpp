#include "stdafx.h"
#include "GameSound.h"
#include "../Player/Player.h"


CGameSound::CGameSound()
{
}


CGameSound::~CGameSound()
{
}


bool CGameSound::Start()
{
	m_bgmVolume = MASTER_VOLUME;
	m_backSound[enTitleBgm].m_backSound.Init("Assets/sound/BackSound/TitleBgm.wav");
	m_backSound[enTitleBgm].m_backSound.SetVolume(m_backSound[enTitleBgm].m_volume);

	m_backSound[enTownBgm].m_backSound.Init("Assets/sound/BackSound/TownBgm.wav");
	m_backSound[enTownBgm].m_backSound.SetVolume(m_backSound[enTownBgm].m_volume);
	m_backSound[enTownBgm].m_soundPosition = { 0.04f, 0.20f, 0.51f };
	m_backSound[enTownBgm].m_lenght = 80.0f;
	m_backSound[enTownBgm].m_isMapSound = true;
	
	m_backSound[enShopBgm].m_backSound.Init("Assets/sound/BackSound/ShopBgm.wav");
	m_backSound[enShopBgm].m_backSound.SetVolume(m_backSound[enShopBgm].m_volume);

	m_backSound[enWorldBgm].m_backSound.Init("Assets/sound/BackSound/FieldBgm.wav");
	m_backSound[enWorldBgm].m_backSound.SetVolume(m_backSound[enWorldBgm].m_volume);
	m_backSound[enWorldBgm].m_isMapSound = true;

	m_backSound[enBossBgm].m_backSound.Init("Assets/sound/BackSound/BossBgm.wav");
	m_backSound[enBossBgm].m_backSound.SetVolume(m_backSound[enBossBgm].m_volume);

	m_backSound[enDeathBgm].m_backSound.Init("Assets/sound/BackSound/BossBgm.wav");
	m_backSound[enDeathBgm].m_backSound.SetVolume(m_backSound[enDeathBgm].m_volume);

	m_backSound[m_soundState].m_backSound.Play(m_backSound[enDeathBgm].m_isLoop, m_backSound[enDeathBgm].m_isBegin);
	return true;
}

void CGameSound::Update()
{

	switch (m_soundState)
	{
	case enTitleBgm:

		break;
	case enWorldBgm:
		
		break;
	case enTownBgm:
		
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
	m_backSound[m_soundState].m_backSound.Update();
	m_backSound[m_soundState].m_backSound.SetVolume(m_bgmVolume);
	SoundLenght();
}

void CGameSound::FadeSound()
{
	if (!m_isFade ) { return; }

	switch (m_state)
	{
	case	enFadeOut:
		m_fadeTime += GameTime().GetDeltaFrameTime();
		if (m_fadeTime < FADE_OUT_TIME)
		{
			m_bgmVolume = (min((m_fadeTime / FADE_OUT_TIME), m_backSound[m_soundState].m_volume));
		}
		else
		{
			m_isFade = false;
			m_fadeTime = 0;
			m_bgmVolume = m_backSound[m_soundState].m_volume;
		}

		break;

	case enFadeIn:
		m_fadeTime += GameTime().GetDeltaFrameTime();
		if (m_fadeTime < FADE_IN_TIME)
		{
			m_bgmVolume = max((m_backSound[m_soundState].m_volume - (m_fadeTime / FADE_IN_TIME)), 0.0f);
		}
		else
		{
			m_isFade = false;
			m_fadeTime = 0.0f;
			m_bgmVolume = 0.0f;

		}
		break;
	}
	
	m_backSound[m_soundState].m_backSound.SetVolume(m_bgmVolume);
	
}

void CGameSound::SoundLenght()
{
	if (&GetPlayer() == nullptr || !m_backSound[m_soundState].m_isMapSound) { return; }

	float oldlen = 99999;
	for (auto vect : m_soundPointList)
	{
		CVector3 soundVec = vect - GetPlayer().GetPosition();
		float len = soundVec.Length();
		if (oldlen > len)
		{
			oldlen = len;

		}
	}

	if (m_backSound[enTownBgm].m_lenght < oldlen)
	{
		oldlen -= m_backSound[enTownBgm].m_lenght;
		if (oldlen < m_volumeDownLen)
		{
			if (m_soundState == enWorldBgm)
			{
				m_backSound[m_soundState].m_backSound.Stop();
				m_soundState = enTownBgm;
				m_backSound[m_soundState].m_backSound.Play(true, false);
			}
			m_bgmVolume = m_backSound[m_soundState].m_volume - (1.0f / m_volumeDownLen * oldlen);
			
		}
		else if(m_soundState != enWorldBgm)
		{
			m_bgmVolume = 0.0f;
			m_backSound[m_soundState].m_backSound.Stop();
			m_soundState = enWorldBgm;
			m_backSound[m_soundState].m_backSound.Play(true,true);
			m_bgmVolume = m_backSound[m_soundState].m_volume;
		}
	}
	else
	{
		m_bgmVolume = m_backSound[m_soundState].m_volume;
	}
}