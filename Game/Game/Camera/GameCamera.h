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
		Engine().SetCamera(nullptr);
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

private:
	//��]
	//target	�^�[�Q�b�g�̍��W
	//position	�J�����̍��W
	void Rotation(CVector3& target, CVector3& position);

	//���b�N�I������Ώۂ�T��
	void SearchTarget();

	//���b�N�I������
	//target	�^�[�Q�b�g�̍��W
	//position	�J�����̍��W
	void LockOn(CVector3& target, CVector3& position);

	//���b�N�I������������
	//target	�^�[�Q�b�g�̍��W
	//position	�J�����̍��W
	void LockOnCancel(CVector3& target, CVector3& position);

	static CGameCamera* m_gameCamera;			//�Q�[���J����
	CCamera				m_camera;				//�J����
	CSpringCamera		m_springCamera;			//�o�l�J����
	CShakeCamera		m_shakeCamera;			//�h��J����
	IEnemy*				m_rockOnEnemy;			//���b�N�I�����Ă���G�l�~�[
	float				m_cameraLength = 0.0f;	//�����_����J�����ւ̋���
	const float			LOCKON_OFFSET_Y = 2.5f;	//���b�N�I�����̍����␳�̌��E�l
	const float			TARGET_OFFSET_Y = 1.4f; //�J�����ʏ펞�̍����␳
	float				m_height = 0.0f;		//�J�����̍��W�ƒ����_�̍���
	bool				m_isLockOn = false;		//���b�N�I�����Ă��邩
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}