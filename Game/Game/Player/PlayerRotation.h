#pragma once

class CPlayerRotation
{
public:
	CPlayerRotation();
	~CPlayerRotation();
	void Update();
	void WeaponRot();

	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

private:
	bool m_isActive = true;

};

