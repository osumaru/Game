#pragma once
class CPlayerArrow : public IGameObject
{
public:
	CPlayerArrow();
	~CPlayerArrow();
	bool Start();
	void Update();
	void Draw();
	const CVector3 getArrowPosition()
	{
		return m_arrowPosition;
	}
private:
	CSkinModel		m_arrowskin;
	CVector3		m_arrowPosition;
	CQuaternion		m_arrowRot;
	CVector3		m_scale = CVector3::Zero;
	CVector3		m_moveSpeed = CVector3::Zero;
	float			m_lifeTime = 0.0f;
	bool			m_isMove = false;
	const float		GRAVITY = -1.5f;
};

