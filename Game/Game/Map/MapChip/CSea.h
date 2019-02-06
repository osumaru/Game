#pragma once
class CSea : public IGameObject
{
public:
	CSea();
	~CSea();
	bool Init(const CVector3& position, const CQuaternion& rotation);
	void Update();
	void Draw();
private:
	CVector3		m_position;
	CQuaternion		m_rotation;
	CSkinModel		m_skinModel;
	CLight			m_light;
};

