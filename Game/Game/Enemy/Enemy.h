#pragma once

class Enemy : public GameObject
{
public:
	void Init(Vector3 position);

	void Update();

	void Draw();

	Vector3 GetPosition()
	{
		return m_position;
	}
private:
	Vector3				m_position;
	SkinModel			m_skinmodel;
	CharacterController m_characterController;
};