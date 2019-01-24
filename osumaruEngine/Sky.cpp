#include "engineStdafx.h"
#include "Sky.h"
#include "Camera/Camera.h"

void CSky::Init(const CCamera* camera)
{
	m_skinModel.Load(L"Assets/modelData/Skyball_WithCap.cmo");
	m_skinModel.SetIsDiffuse(false);
	m_camera = camera;
	m_light.SetAmbientLight(CVector4::White);
	m_skinModel.SetLight(Light());
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}

void CSky::Update()
{
	m_skinModel.Update(m_position, CQuaternion::Identity, CVector3::One);
}

void CSky::Draw()
{
	if (m_camera == nullptr)
	{
		return;
	}
	m_skinModel.Draw(m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
}