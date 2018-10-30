/*
*	�Q�[���J�����N���X
*/

#pragma once
#include "NormalGameCamera.h"
#include "ArrowGameCamera.h"

class CGameCamera : public IGameObject
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
		return *m_gameCamera;
	}

	//�C���X�^���X�̐���
	static void CGameCamera::Create()
	{
		if (!m_gameCamera)
		{
			m_gameCamera = New<CGameCamera>(1);
		}
	}

	//�C���X�^���X�̏���
	static void CGameCamera::Destroy()
	{
		Delete(m_gameCamera);
		m_gameCamera = nullptr;
	}

	//�J�������擾
	const CCamera& GetCamera()
	{
		return m_camera;
	}

	//�o�l�J�����̎擾
	const CSpringCamera& GetSpringCamera()
	{
		return m_springCamera;
	}

	//�J�����̃|�W�V������ݒ�
	//�������@�J�����̍��W�@�������@�^�[�Q�b�g�̍��W
	void SetCameraPosition(const CVector3 pos,const CVector3 tag)
	{

		m_springCamera.SetTarPosition(pos);
		m_springCamera.SetTarTarget(tag);
	}

	//�r���[�s����擾
	CMatrix GetViewMatrix()
	{
		return m_camera.GetViewMatrix();
	}

	//�v���W�F�N�V�����s����擾
	CMatrix GetProjectionMatrix()
	{
		return m_camera.GetProjectionMatrix();
	}

	////�o�l�J�����̃v���W�F�N�V�����s��̎擾
	//const CMatrix GetSpringProjectionMatrix()
	//{
	//	return m_springCamera.GetProjectionMatrix();
	//}
	////�o�l�J�����̃r���[�s��̎擾
	//const CMatrix GetSpringViewMatrix()
	//{
	//	return m_springCamera.GetSpringViewMatrix();
	//}
	void SetCmareaState(EnCameraState cameraState)
	{
		m_cameraState = cameraState;
	}

private:
	static CGameCamera* m_gameCamera;							//�Q�[���J����
	CCamera				m_camera;								//�J����
	EnCameraState		m_cameraState = EnCameraState::enNormal;//�J�����X�e�[�g
	CNormalGameCamera	m_normalCamera;							//�m�[�}���J����
	CArrowGameCamera	m_arrowCamera;							//�A���[�J����
	CVector3			m_cameraVec;							//�����_����J�����ւ̃x�N�g��
	CSpringCamera		m_springCamera;							//�o�l�J����
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}