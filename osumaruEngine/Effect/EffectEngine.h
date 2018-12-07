#pragma once
#include "Effect.h"

class CEffectEngine : Uncopyable
{
public:
	void Init();

	void Update();

	void Draw();

	void SetCamera(CCamera* camera)
	{
		m_pCamera = camera;
	}

	Effekseer::Handle Play(CEffect& effect);

	Effekseer::Manager* GetEffectManager()
	{
		return m_manager;
	}
private:
	CCamera*						m_pCamera = nullptr;
	Effekseer::Manager*				m_manager = nullptr;
	EffekseerRenderer::Renderer*	m_renderer = nullptr;
};