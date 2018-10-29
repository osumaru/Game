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
	const float CAMERA_Y_UP_LIMIT = 0.5f;		//ƒJƒƒ‰‚ÌY•ûŒü‚Ì‰æŠp‚Ì§ŒÀ(ã)
	const float CAMERA_Y_DOWN_LIMIT = 0.5f;		//ƒJƒƒ‰‚ÌY•ûŒü‚Ì‰æŠp‚Ì§ŒÀ(‰º)
	const float TARGET_OFFSET_Y = 1.5f;
};

