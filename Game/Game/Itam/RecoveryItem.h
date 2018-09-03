#pragma once

class CRecoveryItem : public GameObject
{
public:
	void Init(Vector3 position);

	void Update();

	void Draw();

private:
	SkinModel m_skinModel;
	Vector3 m_position;
};
