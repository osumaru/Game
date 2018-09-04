/*
*	敵のインターフェースクラス
*/

#pragma once

class IEnemy : public IGameObject
{
public:
	IEnemy();
	~IEnemy();

	virtual void Init(CVector3 position) = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	CVector3 GetPosition()
	{
		return m_position;
	}

protected:
	CSkinModel				m_skinModel;
	CCharacterController	m_characterController;
	CVector3				m_position;
};