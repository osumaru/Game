#include "Effect.h"

void CEffect::Init(wchar_t* filepath)
{
	m_renderer = EffekseerRendererDX11::Renderer::Create(
		Engine().GetDevice(),
		Engine().GetDeviceContext(),
		2000);
	m_manager = Effekseer::Manager::Create(10000);

	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
	m_effect = Effekseer::Effect::Create(m_manager, (EFK_CHAR*)L"Assets/effect.efk");
}

void CEffect::Play()
{
	m_manager->Play(m_effect, 0.0f, 0.0f, 0.0f);

}

void CEffect::Update(CMatrix mat1, CMatrix mat2)
{
	Effekseer::Matrix44 matt1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matt1.Values[j][i] = mat1.m[j][i];
		}
	}
	Effekseer::Matrix44 matt2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matt2.Values[j][i] = mat2.m[j][i];
		}
	}
	m_renderer->SetCameraMatrix(matt1);
	m_renderer->SetProjectionMatrix(matt2);
	m_manager->Update(GameTime().GetDeltaFrameTime() * 60.0f);
}

void CEffect::Draw()
{
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();
}