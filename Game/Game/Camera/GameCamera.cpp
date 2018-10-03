#include "stdafx.h"
#include "GameCamera.h"
#include "Player\Player.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"

void CGameCamera::Init()
{
	camera.Init();
	camera.SetFar(300.0f);
	camera.SetNear(1.0f);
	camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	camera.SetAngle(CMath::DegToRad(60.0f));
	camera.SetPosition({ 0.0f, 1.8f, 2.8f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	camera.SetUp({ 0.0f, 1.0f, 0.0f });
	camera.Update();
	Add(this, 0);
	m_cameraVec = camera.GetPosition();
	PhysicsWorld().SetCamera(&camera);

	m_springCamera.Init(camera.GetTarget(), camera.GetPosition(), 1.0f);
	
}

void CGameCamera::Update()
{
	float rStick_x = Pad().GetRightStickX() * 10 * GameTime().GetDeltaFrameTime();
	float rStick_y = Pad().GetRightStickY() * GameTime().GetDeltaFrameTime();
	m_cameraVec = camera.GetPosition() - camera.GetTarget();
	if (fabsf(rStick_x) > 0.0f) {
		//Y������̉�]
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x);
		matrix.Mul(m_cameraVec);
	}
	if (fabsf(rStick_y) > 0.0f) {
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

		if (cameraDir.y < -0.9f) {
			m_cameraVec = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f) {
			m_cameraVec = cameraVecOld;
		}
	}

	//�v���C���[�̌��ɒǏ]����J����
	{
		CVector3 position, toCameraXZ;
		position = GetPlayer().GetPosition();
		toCameraXZ = m_cameraVec;
		float height = toCameraXZ.y;
		toCameraXZ.y = 0.0f;
		float toCameraLen = toCameraXZ.Length();
		toCameraXZ.Normalize();

		CVector3 target = GetPlayer().GetPosition();
		target.y += 1.5f;
		CVector3	toNewCameraPos = camera.GetPosition() - target;
		toNewCameraPos.y = 0.0f;
		toNewCameraPos.Normalize();

		float weight = 0.7f;  //���̃E�F�C�g�̒l��0.0�`1.0�̒l���Ƃ�B1.0�ɋ߂Â��قǒǔ��������Ȃ�B
		toNewCameraPos = toNewCameraPos * weight + toCameraXZ * (1.0f - weight);
		toNewCameraPos.Normalize();
		toNewCameraPos *= toCameraLen;
		toNewCameraPos.y = height;              //������߂��B
		CVector3 pos = target + toNewCameraPos;  //����ŐV�������_������B

		camera.SetPosition(pos);
		camera.SetTarget(target);
	}
	//float interporation = 2.0f;
	//position.y += interporation;	
	//camera.SetTarget(position);
	//m_springCamera.SetTarTarget(position);

	////position.y -= interporation;
	//position += m_cameraVec;
	//camera.SetPosition(position);
	////m_springCamera.SetTarPosition(position);

	////m_springCamera.Update();
	camera.Update();
}