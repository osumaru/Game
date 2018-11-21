#include "stdafx.h"
#include "Fade.h"



CFade::CFade()
{
}


CFade::~CFade()
{
}

bool CFade::Start()
{
	m_fadeTexture.Load(L"Assets/sprite/Fade.png");
	m_fadeSprite.Init(&m_fadeTexture);
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
				m_fadeSprite.SetAlpha(m_texturerAlpha);
			}
			else
			{
				m_isExecute = false;
				m_fadeTime = 0;
				m_texturerAlpha = 0;
				m_loadScene.IsDraw(true);
			}

			break;

		case enFadeIn:
			m_fadeTime += GameTime().GetDeltaFrameTime();
			if (m_fadeTime < FADE_IN_TIME)
			{
				m_texturerAlpha = max((1 - (m_fadeTime / FADE_IN_TIME)), 0.0f);
				m_fadeSprite.SetAlpha(m_texturerAlpha);
			}
			else
			{
				m_isExecute = false;
				m_fadeTime = 0;
				m_texturerAlpha = 1.0f;
				m_loadScene.IsDraw(false);
				
			}
			break;
		}
	}
}

void CFade::AfterDraw()
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

}
void CFade::FadeIn()
{
	m_fadeTime = 0.0f;
	m_isExecute = true;
	m_fadeState = enFadeIn;
}



