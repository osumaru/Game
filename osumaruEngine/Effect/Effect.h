#pragma once

class CEffect
{
public:
	void Init(wchar_t* filepath);

	void Play();

	void Update(CMatrix mat1, CMatrix mat2);

	void Draw();

private:
	Effekseer::Effect*				m_effect = nullptr;
	//Effekseer::Handle				m_handle = -1;
	Effekseer::Manager*				m_manager = nullptr;
	EffekseerRenderer::Renderer*	m_renderer = nullptr;
};