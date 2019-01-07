#pragma once

class CTBDR : Uncopyable
{
public:
	void Init();

	void Draw();

	void SetCamera(const CCamera* camera)
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
	CShader									m_cs;
	CConstantBuffer							m_pointLightCB;
	const CCamera*							m_camera = nullptr;					//�萔�o�b�t�@�̍X�V�Ɏg���Q�[���J����
};