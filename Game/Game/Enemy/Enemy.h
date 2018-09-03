#pragma once

class CEnemy : public IGameObject
{
public:
	void Init(CVector3 position);

	void Update();

	void Draw();

	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	CVector3				m_position;
	CSkinModel			m_skinmodel;
	CCharacterController m_characterController;
};