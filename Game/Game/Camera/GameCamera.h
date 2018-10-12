/*
*	�Q�[���J�����N���X
*/

#pragma once
#include "NormalGameCamera.h"
#include "ArrowGameCamera.h"

class CGameCamera : IGameObject
{
public:

	enum EnCameraState 
	{
		enNormal,
		enArrow,
		enFree,
		enNum,
	};
	//������
	void Init();

	//�X�V
	void Update();

	//�Q�[���J�����̃C���X�^���X���擾
	static CGameCamera& GetInstance()
	{
		static CGameCamera gamecamera;
		return gamecamera;
	}

	//�J�������擾
	const CCamera& GetCamera()
	{
		return camera;
	}

	//�J�����̃|�W�V������ݒ�
	//�������@�J�����̍��W�@�������@�^�[�Q�b�g�̍��W
	void SetCameraPosition(const CVector3 pos,const CVector3 tag)
	{
		camera.SetPosition(pos);
		camera.SetTarget(tag);
	}

	//�r���[�s����擾
	CMatrix GetViewMatrix()
	{
		return camera.GetViewMatrix();
		//return m_springCamera.GetSpringViewMatrix();
	}

	//�v���W�F�N�V�����s����擾
	CMatrix GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
		//return m_springCamera.GetProjectionMatrix();
	}

	//�o�l�J�����̃v���W�F�N�V�����s��̎擾
	const CMatrix GetSpringProjectionMatrix()
	{
		return m_springCamera.GetProjectionMatrix();
	}
	//�o�l�J�����̃r���[�s��̎擾
	const CMatrix GetSpringViewMatrix()
	{
		return m_springCamera.GetSpringViewMatrix();
	}
	void SetCmareaState(EnCameraState cameraState)
	{
		m_cameraState = cameraState;
	}

private:
	CCamera camera;			//�J����
	EnCameraState	m_cameraState = EnCameraState::enNormal;
	CNormalGameCamera	m_normalCamera;
	CArrowGameCamera	m_arrowCamera;

	CVector3 m_cameraVec;	//�����_����J�����ւ̃x�N�g��
	CSpringCamera	m_springCamera;

};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}