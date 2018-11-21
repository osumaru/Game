#include "stdafx.h"
#include "NormalGameCamera.h"
#include "../Player/Player.h"
#include "GameCamera.h"


CNormalGameCamera::CNormalGameCamera()
{
}


CNormalGameCamera::~CNormalGameCamera()
{
}

void CNormalGameCamera::Start(const CVector3 pos, const CVector3 tag)
{
	m_pPlayerBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Spine2");
	m_cameraPosition = pos;
	m_targetPosition = tag;
}

void CNormalGameCamera::Update()
{
	float rStick_x = Pad().GetRightStickX();
	float rStick_y = Pad().GetRightStickY();

	CVector3	oldCameraVec = GetGameCamera().GetSpringCamera().GetPosition() - GetGameCamera().GetSpringCamera().GetTarget();
	m_cameraVec = m_cameraPosition - m_targetPosition;
	if (oldCameraVec.Length() < m_cameraVec.Length())
	{
		float len = m_cameraVec.Length() / oldCameraVec.Length();
		m_cameraVec = oldCameraVec * len;
	}

	if (fabsf(rStick_x) > 0.0f) {
		//Y軸周りの回転
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		matrix.Mul(m_cameraVec);
	}

	if (fabsf(rStick_y) > 0.0f)
	{
		//X軸周りの回転
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, m_cameraVec);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, rStick_y * CAMERA_SPEED / 2 * GameTime().GetDeltaFrameTime());
		//1フレーム前のカメラベクトル
		CVector3 cameraVecOld = m_cameraVec;

		matrix.Mul(m_cameraVec);
		CVector3 cameraDir = m_cameraVec;
		cameraDir.Normalize();

		if (cameraDir.y < -0.8f)
		{
			m_cameraVec = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f)
		{
			m_cameraVec = cameraVecOld;

		}

	}

		CVector3 toCameraXZ;
		toCameraXZ = m_cameraVec;
		float height = toCameraXZ.y;
		toCameraXZ.y = 0.0f;
		float toCameraLen = toCameraXZ.Length();
		toCameraXZ.Normalize();
		//注視点の設定
		CVector3 target = GetPlayer().GetPosition();
		target.x = m_pPlayerBoneMat->m[3][0];
		target.y = m_pPlayerBoneMat->m[3][1];
		target.z = m_pPlayerBoneMat->m[3][2];
		//target.y += TARGET_OFFSET_Y;

		CVector3	toNewCameraPos = m_cameraPosition - target;
		toNewCameraPos.y = 0.0f;
		toNewCameraPos.Normalize();
		float weight = 0.75f;  //このウェイトの値は0.0～1.0の値をとる。1.0に近づくほど追尾が強くなる。
		toNewCameraPos = toNewCameraPos * weight + toCameraXZ * (1.0f - weight);
		toNewCameraPos.Normalize();
		toNewCameraPos *= toCameraLen;
		toNewCameraPos.y = height;              //高さを戻す。


		CVector3 pos = target + toNewCameraPos;  //これで新しい視点が決定。
		GetGameCamera().SetCameraPosition(pos, target);
		m_cameraPosition = pos;
		m_targetPosition = target;
	
}