#pragma once
class CNormalGameCamera	
{
public:
	CNormalGameCamera();
	~CNormalGameCamera();
	void Start(const CVector3 pos, const CVector3 tag);
	void Update();
private:
	CVector3	m_cameraPosition;
	CVector3	m_targetPosition;
	CVector3	m_cameraVec;

};

