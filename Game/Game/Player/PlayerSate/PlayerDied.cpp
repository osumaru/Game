#include "stdafx.h"
#include "../Player.h"
#include "PlayerDied.h"
#include "../../Scene/SceneManager.h"


void CPlayerDied::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDete, 0.2f);
	/*CSoundSource* GameOverSound = New<CSoundSource>(0);
	GameOverSound->Init("Assets/sound/SystemSound/GameOver.wav");
	GameOverSound->Play(false);
	GameOverSound->SetVolume(GameOverVolume);*/
}

void CPlayerDied::Update()
{
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		m_pPlayerGetter->SetIsDied(true);
		const float GameOverVolume = 0.3f;
		GetSceneManager().GetGameSound()->SetGameSound(CGameSound::enDeathBgm);
	}

}
