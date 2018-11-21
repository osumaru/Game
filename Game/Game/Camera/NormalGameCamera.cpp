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
		//Y������̉�]
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		matrix.Mul(m_cameraVec);
	}

	if (fabsf(rStick_y) > 0.0f)
	{
		//X������̉�]
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, m_cameraVec);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, rStick_y * CAMERA_SPEED / 2 * GameTime().GetDeltaFrameTime());
		//1�t���[���O�̃J�����x�N�g��
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
		//�����_�̐ݒ�
		CVector3 target = GetPlayer().GetPosition();
		target.x = m_pPlayerBoneMat->m[3][0];
		target.y = m_pPlayerBoneMat->m[3][1];
		target.z = m_pPlayerBoneMat->m[3][2];
		//target.y += TARGET_OFFSET_Y;

		CVector3	toNewCameraPos = m_cameraPosition - target;
		toNewCameraPos.y = 0.0f;
		toNewCameraPos.Normalize();
		float weight = 0.75f;  //���̃E�F�C�g�̒l��0.0�`1.0�̒l���Ƃ�B1.0�ɋ߂Â��قǒǔ��������Ȃ�B
		toNewCameraPos = toNewCameraPos * weight + toCameraXZ * (1.0f - weight);
		toNewCameraPos.Normalize();
		toNewCameraPos *= toCameraLen;
		toNewCameraPos.y = height;              //������߂��B


		CVector3 pos = target + toNewCameraPos;  //����ŐV�������_������B
		GetGameCamera().SetCameraPosition(pos, target);
		m_cameraPosition = pos;
		m_targetPosition = target;
	
}