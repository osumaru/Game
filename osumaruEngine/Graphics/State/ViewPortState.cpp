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
}