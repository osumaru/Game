#include "EffectEngine.h"
#include "../Camera/Camera.h"

void CEffectEngine::Init()
{
	m_renderer = EffekseerRendererDX11::Renderer::Create(
		GetDevice(),
		GetDeviceContext(),
		2000);
	m_manager = Effekseer::Manager::Create(10000);

	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
}

void CEffectEngine::Update()
{
	if (m_pCamera != nullptr)
	{
		Effekseer::Matrix44 viewMat;
		memcpy(viewMat.Values, m_pCamera->GetViewMatrix().m, sizeof(viewMat.Values));
		Effekseer::Matrix44 projMat;
		memcpy(projMat.Values, m_pCamera->GetProjectionMatrix().m, sizeof(projMat.Values));

		m_renderer->SetCameraMatrix(viewMat);
		m_renderer->SetProjectionMatrix(projMat);
	}
	m_manager->Update(GameTime().GetDeltaFrameTime() * 60.0f);
}

Effekseer::Handle CEffectEngine::Play(CEffect& effect)
{
	CVector3 position = effect.GetPosition();
	Effekseer::Handle handle = m_manager->Play(effect.GetBody(), 0.0f, 0.0f, 0.0f);
	
	return handle;
	
}

void CEffectEngine::Draw()
{
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();
}