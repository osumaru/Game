#include "engineStdafx.h"
#include "ViewPortState.h"
#include "../PreRendering/ShadowMap.h"

void CViewPortState::Init()
{
	m_viewPort[enViewPortGame].TopLeftX = 0;
	m_viewPort[enViewPortGame].TopLeftY = 0;
	m_viewPort[enViewPortGame].Width = FrameBufferWidth();
	m_viewPort[enViewPortGame].Height = FrameBufferHeight();
	m_viewPort[enViewPortGame].MinDepth = 0.0f;
	m_viewPort[enViewPortGame].MaxDepth = 1.0f;

	m_viewPort[enViewPortShadow].TopLeftX = 0;
	m_viewPort[enViewPortShadow].TopLeftY = 0;
	m_viewPort[enViewPortShadow].Width = CShadowMap::GetShadowMapSize();
	m_viewPort[enViewPortShadow].Height = CShadowMap::GetShadowMapSize();
	m_viewPort[enViewPortShadow].MinDepth = 0.0f;
	m_viewPort[enViewPortShadow].MaxDepth = 1.0f;
	
	m_viewPort[enViewPortBloomCombine].TopLeftX = 0;
	m_viewPort[enViewPortBloomCombine].TopLeftY = 0;
	m_viewPort[enViewPortBloomCombine].Width = FrameBufferWidth() / 2.0f;
	m_viewPort[enViewPortBloomCombine].Height = FrameBufferHeight() / 2.0f;
	m_viewPort[enViewPortBloomCombine].MinDepth = 0.0f;
	m_viewPort[enViewPortBloomCombine].MaxDepth = 1.0f;

	int count = 0;
	float frameWidth = FrameBufferWidth();
	float frameHeight = FrameBufferHeight();
	for (int i = enViewPortBloom00; i <= enViewPortBloom41; i++)
	{
		if (i % 2 == 0)
		{
			frameWidth /= 2.0f;
		}
		if (i % 2 == 1)
		{
			frameHeight /= 2.0f;
		}
		m_viewPort[i].TopLeftX = 0;
		m_viewPort[i].TopLeftY = 0;
		m_viewPort[i].Width = frameWidth;
		m_viewPort[i].Height = frameHeight;
		m_viewPort[i].MinDepth = 0.0f;
		m_viewPort[i].MaxDepth = 1.0f;
	}
}