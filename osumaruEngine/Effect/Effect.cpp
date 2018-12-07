#include "Effect.h"
#include "EffectEngine.h"
#include "../Resource/EffectResource.h"


void CEffect::Init(wchar_t* filepath)
{

	m_effect = Engine().GetEffectResource().Load(filepath);
}

void CEffect::Play()
{
	m_handle = Engine().GetEffectEngine().Play(*this);
}

void CEffect::Update()
{
	Effekseer::Manager* manager = Engine().GetEffectEngine().GetEffectManager();
	CMatrix worldMat;
	CMatrix rotMat;
	CMatrix transMat;
	rotMat.MakeRotationFromQuaternion(m_rotation);
	transMat.MakeTranslation(m_position);
	worldMat.Mul(rotMat, transMat);
	Effekseer::Matrix43 mat;
	for (int i = 0; i < 4; i++)
	{
		memcpy(mat.Value[i], worldMat.m[i], sizeof(mat.Value[i]));
	}
	manager->SetMatrix(m_handle, mat);
}