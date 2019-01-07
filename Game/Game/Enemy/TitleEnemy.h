#pragma once

class CTitleEnemy : public IGameObject
{
public:
	void Init(const wchar_t* modelName, CVector3 position);

	void Update() override;

	void Draw() override;
private:
	CSkinModel m_skinModel;
	CAnimation m_animation;
	CVector3 m_position;
	CQuaternion m_rotation;
};