/*
*	�Q�[���J�����N���X
*/

#pragma once

class CGameCamera : IGameObject
{
public:
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

private:
	CCamera camera;			//�J����
	CVector3 m_cameraVec;	//�����_����J�����ւ̃x�N�g��
	CSpringCamera	m_springCamera;
	CVector3 m_arrowCamera;	//�|���\���Ă��鎞�̃J�����̈ʒu

};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}