#include "stdafx.h"
#include "Fade.h"
#include "../../Scene/SceneManager.h"



CFade::CFade()
{
}


CFade::~CFade()
{
}

bool CFade::Start()
{
	m_fadeTexture = TextureResource().LoadTexture(L"Assets/sprite/Fade.png");
	m_fadeSprite.Init(m_fadeTexture);
	m_fadeSprite.SetPosition(m_texturePosition);
	m_fadeSprite.SetSize(m_textureSize);
	m_fadeSprite.SetAlpha(m_texturerAlpha);
	m_loadScene.Start();
	return true;
}
void CFade::Update()
{
	if (m_isExecute)
	{
		switch (m_fadeState)
		{
		case enFadeOut:
			m_fadeTime += GameTime().GetDeltaFrameTime();
			if (m_fadeTime < FADE_OUT_TIME)
			{
				m_texturerAlpha = (min((m_fadeTime / FADE_OUT_TIME), 1.0f));
			}
			else
			{
				m_isExecute = false;
				m_fadeTime = 0;
				m_texturerAlpha = 1.0f;
				m_loadScene.IsDraw(true);
			}
			m_fadeSprite.SetAlpha(m_texturerAlpha);

			break;

		case enFadeIn:
			m_fadeTime += GameTime().GetDeltaFrameTime();
			if (m_fadeTime < FADE_IN_TIME)
			{
				m_texturerAlpha = max((1 - (m_fadeTime / FADE_IN_TIME)), 0.0f);
			}
			else
			{
				m_isExecute = false;
				m_fadeTime = 0.0f;
				m_texturerAlpha = 0.0f;
			}
			m_fadeSprite.SetAlpha(m_texturerAlpha);
			break;
		}
	}
}

void CFade::PostAfterDraw()
{
	//ŽÀsŽžˆÈŠO‚Í•`‰æ‚µ‚È‚¢
	//if (!m_isExecute){return;}
	m_fadeSprite.Draw();
	m_loadScene.AfterDraw();
}

void CFade::FadeOut()
{
	m_fadeTime = 0.0f;
	m_isExecute = true;
	m_fadeState = enFadeOut;
	GetSceneManager().GetGameSound()->GamesoundFadeIn();

}
void CFade::FadeIn()
{
	m_fadeTime = 0.0f;
	m_isExecute = true;
	m_fadeState = enFadeIn;
	m_loadScene.IsDraw(false);
	GetSceneManager().GetGameSound()->GamesoundFadeOut();
}



