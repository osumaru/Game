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

	m_viewPort[enViewPortShadow1].TopLeftX = 0;
	m_viewPort[enViewPortShadow1].TopLeftY = 0;
	m_viewPort[enViewPortShadow1].Width = CShadowMap::GetShadowMapSize();
	m_viewPort[enViewPortShadow1].Height = CShadowMap::GetShadowMapSize();
	m_viewPort[enViewPortShadow1].MinDepth = 0.0f;
	m_viewPort[enViewPortShadow1].MaxDepth = 1.0f;

	m_viewPort[enViewPortShadow2].TopLeftX = 0;
	m_viewPort[enViewPortShadow2].TopLeftY = 0;
	m_viewPort[enViewPortShadow2].Width = CShadowMap::GetShadowMapSize() >> 1;
	m_viewPort[enViewPortShadow2].Height = CShadowMap::GetShadowMapSize() >> 1;
	m_viewPort[enViewPortShadow2].MinDepth = 0.0f;
	m_viewPort[enViewPortShadow2].MaxDepth = 1.0f;

	m_viewPort[enViewPortShadow3].TopLeftX = 0;
	m_viewPort[enViewPortShadow3].TopLeftY = 0;
	m_viewPort[enViewPortShadow3].Width = CShadowMap::GetShadowMapSize() >> 2;
	m_viewPort[enViewPortShadow3].Height = CShadowMap::GetShadowMapSize() >> 2;
	m_viewPort[enViewPortShadow3].MinDepth = 0.0f;
	m_viewPort[enViewPortShadow3].MaxDepth = 1.0f;
	
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