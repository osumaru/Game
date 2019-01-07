/*
*	�Q�[���J�����N���X
*/

#pragma once
#include "NormalGameCamera.h"
#include "ArrowGameCamera.h"

class IEnemy;

class CGameCamera : public IGameObject
{
public:
	//������
	void Init();
	
	//�X�V
	void Update();

	//��]
	void Rotation();
	
	//�J�����K�v�ȃv���C���[�̏��̏�����`
	void CameraSetPlayer();

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
			m_gameCamera = New<CGameCamera>(PRIORITY_CAMERA);
		}
	}

	//�C���X�^���X�̏���
	static void CGameCamera::Destroy()
	{
		Delete(m_gameCamera);
		m_gameCamera = nullptr;
		PhysicsWorld().SetCamera(nullptr);
		Engine().GetDeferred().SetCamera(nullptr);
		Sky().SetCamera(nullptr);
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

	//�h��J�����̎擾
	CShakeCamera& GetShakeCamera()
	{
		return m_shakeCamera;
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

	//�G�l�~�[�����b�N�I������
	void RockOnEnemy();

private:
	static CGameCamera* m_gameCamera;							//�Q�[���J����
	CCamera				m_camera;								//�J����
	CVector3			m_cameraVec;							//�����_����J�����ւ̃x�N�g��
	CSpringCamera		m_springCamera;							//�o�l�J����
	CShakeCamera		m_shakeCamera;							//�h��J����
	IEnemy*				m_rockOnEnemy;							//���b�N�I�����Ă���G�l�~�[
	const CMatrix*		m_pPlayerBoneMat;						//�����_�Ƃ���v���C���[�̃{�[���̍s��
	const float			CAMERA_SPEED = 4.0f;					//�J�����̉�]���x
	bool				m_isRockOn = false;						//���b�N�I�����Ă��邩
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}