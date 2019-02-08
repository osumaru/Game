#include "stdafx.h"
#include "CSea.h"
#include "../../Camera/GameCamera.h"
#include"../../Scene/SceneManager.h"


CSea::CSea()
{
}


CSea::~CSea()
{
}

bool CSea::Init(const CVector3& position, const CQuaternion& rotation)
{
	m_skinModel.Load(L"Assets/modelData/Sea.cmo");
	
	m_skinModel.SetIsDiffuse(true);
	m_light = Light();
	m_skinModel.SetLight(m_light);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Map/SeaNormalMap.png");
	m_position = position;
	m_rotation = rotation;

	return true;
}

void CSea::Update()
{
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	if (GetSceneManager().GetSceneChange())
	{
		Delete(this);
		return;
	}
}

void CSea::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}