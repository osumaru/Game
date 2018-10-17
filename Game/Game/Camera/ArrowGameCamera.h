#pragma once
class CArrowGameCamera
{
public:
	CArrowGameCamera();
	~CArrowGameCamera();
	void Start(const CVector3 pos, const CVector3 tag);
	void Update();
private:
	CVector3	m_cameraPosition;
	CVector3	m_targetPosition;
	CVector3	m_cameraVec;
	const float ARROW_CAMERA_SPEED = 2.0f;
};

