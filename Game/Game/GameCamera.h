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

	//�r���[�s����擾
	CMatrix GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}

	//�v���W�F�N�V�����s����擾
	CMatrix GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}



private:
	CCamera camera;			//�J����
	CVector3 m_cameraVec;	//�����_����J�����ւ̃x�N�g��
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}