#pragma once

class CTBDR : Uncopyable
{
public:
	void Init();

	void Draw();

	void SetCamera(CCamera* camera)
	{
		m_camera = camera;
	}

private:
	struct SPointLightCB
	{
		CMatrix viewMat;
		CMatrix projectionMat;
		CMatrix viewMatRotOnry;
		CVector2 screenParam;
	};
	CShader			m_cs;
	CConstantBuffer	m_cb;
	CCamera*		m_camera = nullptr;
};