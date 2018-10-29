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
	CVector3	m_oldVec;
	const CMatrix*	m_pPlayerBoneMat;		//注視点とするプレイヤーのボーンの行列
	const float TARGET_OFFSET_Y = 2.0f;	//ターゲットのＹ方向に対する補正値
	const float CAMERA_SPEED = 10.0f;  //カメラの回転速度

};

