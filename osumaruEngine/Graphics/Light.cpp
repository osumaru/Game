#include "engineStdafx.h"
#include "Light.h"

CLight::CLight() :
	m_ambientLight(CVector4::White),
	m_diffuseLight(),
	m_diffuseLightDirection()
{
	for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++)
	{
		m_diffuseLight[i] = CVector4::Black;
		m_diffuseLightDirection[i] = { 1.0f, 0.0f, 0.0f, 1.0f };
	}
}