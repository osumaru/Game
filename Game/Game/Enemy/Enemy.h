#pragma once

class Enemy : public GameObject
{
public:
	void Init(Vector3 position);

	void Update();

	void Draw();

private:
	Vector3 m_position;
	SkinModel m_skinmodel;
};