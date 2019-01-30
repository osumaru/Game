/*
*	�Q�[���J�����N���X
*/

#pragma once

#include "CameraCollisionSolver.h"

class IEnemy;

class CGameCamera : public IGameObject
{
public:
	//������
	void Init();
	
	//�X�V
	void Update();

	void PostAfterDraw()override;

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

	//�|�������ɃY�[�����Ă��邩���擾
	bool GetIsArrowZoom()
	{
		return m_isArrowZoom;
	}

	//�|�������ɃY�[�����Ă��邩��ݒ�
	//isArrowZoom	�|�������ɃY�[�����Ă��邩
	void SetIsArrowZoom(bool isArrowZoom)
	{
		m_isArrowZoom = isArrowZoom;
	}

private:
	//�J�����ւ̃x�N�g������]����
	void Rotation();

	//���b�N�I������Ώۂ�T��
	void SearchTarget();

	//���b�N�I���Ώۂ�؂�ւ���
	void ChangeTarget();

	//���b�N�I������
	//target	�^�[�Q�b�g�̍��W
	void LockOn(CVector3& target);

	//���b�N�I������������
	void LockOnCancel();

private:
	enum EnLockOnState
	{
		enLockOn_None,	//�����Ȃ�
		enLockOn_Enemy,	//�G�l�~�[
		enLockOn_Boss	//�{�X
	};
	CSprite					m_reticule;
	CSprite					m_lockOnSprite;				//���b�N�I���X�v���C�g				
	static CGameCamera*		m_gameCamera;				//�Q�[���J����
	CCamera					m_camera;					//�J����
	CSpringCamera			m_springCamera;				//�o�l�J����
	CShakeCamera			m_shakeCamera;				//�h��J����
	CCameraCollisionSolver	m_cameraCollisionSolver;	//�J�����̓����蔻��
	EnLockOnState			m_lockOnState = enLockOn_None;	//�������b�N�I�����Ă��邩
	IEnemy*					m_lockOnEnemy = nullptr;	//���b�N�I�����Ă���G�l�~�[
	CVector3				m_toCameraPos;				//�J�����ւ̃x�N�g��
	float					m_cameraLength = 0.0f;		//�����_����J�����ւ̋���
	float					m_preRStick = 0.0f;			//1�t���[���O�̃p�b�h���͗�
	const float				LOCKON_OFFSET_Y = 2.5f;		//���b�N�I�����̍����␳�̌��E�l
	const float				TARGET_OFFSET_Y = 1.4f;		//�J�����ʏ펞�̍����␳
	//float					m_height = 0.0f;			//�J�����̍��W�ƒ����_�̍���
	int						m_lockOnEnemyNumber = 0;	//���b�N�I�����Ă���G�l�~�[�ԍ�
	bool					m_isLockOn = false;			//���b�N�I�����Ă��邩
	bool					m_isArrowZoom = false;		//�|�������ɃY�[�����Ă��邩
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}