#include "stdafx.h"
#include "ArrowGameCamera.h"
#include "../Player/Player.h"
#include "GameCamera.h"


CArrowGameCamera::CArrowGameCamera()
{
}


CArrowGameCamera::~CArrowGameCamera()
{
}

void CArrowGameCamera::Start(const CVector3 pos, const CVector3 tag)
{
	m_cameraPosition = pos;
	m_targetPosition = tag;

}

void CArrowGameCamera::Update()
{
	float rStick_x = Pad().GetRightStickX() * 2 * GameTime().GetDeltaFrameTime();
	float rStick_y = Pad().GetRightStickY() * GameTime().GetDeltaFrameTime();

	//m_cameraVec = m_cameraPosition - m_targetPosition;
	m_cameraVec = GetGameCamera().GetCamera().GetPosition() - GetGameCamera().GetCamera().GetTarget();

	if (fabsf(rStick_x) > 0.0f) {
		//Y������̉�]
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x);
		matrix.Mul(m_cameraVec);
	}

	if (fabsf(rStick_y) > 0.0f)
	{
		//X������̉�]
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, m_cameraVec);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, rStick_y);
		//1�t���[���O�̃J�����x�N�g��
		CVector3 cameraVecOld = m_cameraVec;

		matrix.Mul(m_cameraVec);
		CVector3 cameraDir = m_cameraVec;
		cameraDir.Normalize();

		if (cameraDir.y < -0.3f)
		{
			m_cameraVec = cameraVecOld;
		}
		else if (cameraDir.y > 0.5f)
		{
			m_cameraVec = cameraVecOld;

		}
	}
	//�����_�̐ݒ�
	CVector3 cameraPos;
	CVector3 target = GetPlayer().GetPosition();
	target.y += 1.5f;
	//�v���C���[�̑O�������擾
	CMatrix	mat = GetPlayer().GetPlayerSkin().GetWorldMatrix();
	CVector3 playerFlont = { -mat.m[0][0],-mat.m[0][1],-mat.m[0][2] };
	playerFlont.Normalize();
	target += playerFlont * 0.5f;
	//�^�[�Q�b�g����J�����̏ꏊ�܂ł̒������o��
	CVector3	toNewCameraPos = GetGameCamera().GetCamera().GetPosition() - target;
	toNewCameraPos.Normalize();
	m_cameraVec.Normalize();
	cameraPos = target + m_cameraVec * 2;
	GetGameCamera().SetCameraPosition(cameraPos, target);
	m_cameraPosition = cameraPos;
	m_targetPosition = target;

}