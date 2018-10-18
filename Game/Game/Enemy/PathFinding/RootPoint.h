#pragma once

class CRootPoint : public IGameObject
{
public:
	void Init(CVector3 position, int listNumer);

	bool Start();

	void Update();

	const CVector3& GetPosition()
	{
		return m_position;
	}

	int GetListNumber()
	{
		return m_listNumber;
	}

private:
	CVector3 m_position;
	int      m_listNumber = 0;
};