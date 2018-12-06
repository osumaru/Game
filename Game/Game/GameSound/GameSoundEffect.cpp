#include "stdafx.h"
#include "GameSoundEffect.h"


CGameSoundEffect::CGameSoundEffect()
{
}


CGameSoundEffect::~CGameSoundEffect()
{
}

bool CGameSoundEffect::Start()
{

	m_soundEffect.Init("Assets/sound/SystemSound/MenuOpen.wav",false);

	return true;
}

void CGameSoundEffect::Update()
{


}