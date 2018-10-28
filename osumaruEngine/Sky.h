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
private:
	CSkinModel m_skinModel;
	const CCamera* m_camera;
};

static CSky& Sky()
{
	return CSky::GetInstance();
}