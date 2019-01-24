#pragma once
#include "Graphics/SkinModel.h"
class CCamera;

class CSky : public IGameObject
{
	CSky() {}
	~CSky() {}
public:
	static CSky& GetInstance()
	{
		static CSky instance;
		return instance;
	}

	void Init(const CCamera* camera);

	void Update()override;

	void Draw()override;

	void SetCamera(const CCamera* camera)
	{
		m_camera = camera;
	}

	void SetLight(const CLight& light)
	{
		m_skinModel.SetLight(light);
	}

	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
private:
	CSkinModel m_skinModel;
	const CCamera* m_camera = nullptr;
	CLight m_light;
	CVector3 m_position = CVector3::Zero;
};

static CSky& Sky()
{
	return CSky::GetInstance();
}