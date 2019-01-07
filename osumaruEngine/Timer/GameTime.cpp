#include "engineStdafx.h"
#include "GameTime.h"
#include "../Graphics/Font/Font.h"

void CGameTime::Init()
{
	m_font = new CFont;
	m_font->Init(L"FPS");
	m_font->SetPosition({ -630.0f, 350.0f });
}

void CGameTime::Update(CStopWatch& sw)
{
	float limitTime = 1.0f / 60.0f;
	float deltaTime = sw.GetElapsedTime();
	if (deltaTime < limitTime)
	{
		DWORD sleepTime = max(0.0, limitTime * 1000.0 - (DWORD)sw.GetElapsedTimeMill());
		Sleep(sleepTime);
		deltaTime = limitTime;
	}
	deltaTime = min(1.0f / 10.0f, deltaTime);

	m_frameDeltaTime = deltaTime;
	m_gameDeltaTime = deltaTime;
	if (0.0f < m_slowDelayTime || 0 < m_slowDelayCount )
	{

		m_slowDelayTime -= deltaTime;
		m_slowDelayCount--;
	}
	else
	{
		if (0.0f < m_slowTime || 0 < m_slowCount)
		{
			m_gameDeltaTime *= m_slowScale;
			m_slowTime -= deltaTime;
			m_slowCount--;
		}
	}
	
}

void CGameTime::Draw()
{
	wchar_t fps[24];
	swprintf(fps, L"FPS:%f", 1.0f / m_frameDeltaTime);
	m_font->SetString(fps);
	m_font->Draw();
}