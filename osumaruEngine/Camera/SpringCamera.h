#pragma once
#include "Camera.h"
//�o�l�J����

class CSpringCamera
{
public:
	//�R���X�g���N�^
	CSpringCamera();

	//�f�X�g���N�^
	~CSpringCamera();

	/*
	������
	target			�����X
	position		���W
	maxMoveSpeed	�ő呬�x
	*/
	void Init(const CVector3& target, const CVector3& position, float maxMoveSpeed);


	//�ڕW�ƂȂ钍���_��ݒ�B
	void SetTarTarget(const CVector3& target)
	{
		m_target = target;
	}

	//�����_��ݒ�
	void SetTarget(const CVector3& target)
	{
		m_camera.SetTarget(target);
	}


	//�ڕW�ƂȂ鎋�_��ݒ�
	void SetTarPosition(const CVector3& position)
	{
		m_position = position;
	}

	//���_��ݒ�
	void SetPosition(const CVector3& position)
	{
		m_camera.SetPosition(position);
	}

	//�����ʂ��擾
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}

	//�����_���擾
	const CVector3& GetTarget() const
	{
		return m_camera.GetTarget();
	}

	//���_���擾
	const CVector3& GetPosition() const
	{
		return m_camera.GetPosition();
	}

	//�X�V�֐�
	void Update();

	//�J�������擾
	const CCamera* GetCamera() const
	{
		return &m_camera;
	}

	/*
	�o�l�̌�������ݒ�
	dampingRate		�������A���̒l���傫���قǃJ�������x��Ă��Ă���
	*/
	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}

	//�ڕW�ƂȂ钍���_���擾
	const CVector3& GetTarTarget() const
	{
		return m_target;
	}

	//�ڕW�ƂȂ鎋�_���擾
	const CVector3& GetTarPosition() const
	{
		return m_position;
	}

	//�o�l�J�����p�̃p�����[�^���N���A
	void ClearSpringParame()
	{
		m_target = { 0.0f, 0.0f, 0.0f };
		m_positionMoveSpeed = { 0.0f, 0.0f, 0.0f };
	}

	/*
	�o�l�J�����̍X�V
	�o�l�J�����̂ݍX�V�������Ƃ��Ɏg��
	*/
	void UpdateSpringCamera();

	/*
	�J�����̍X�V
	�J�����̂ݍX�V�������Ƃ��Ɏg��
	*/
	void UpdateCamera()
	{
		m_camera.Update();
	}

	//�v���W�F�N�V�����s����擾
	const CMatrix& GetProjectionMatrix()
	{
		return m_camera.GetProjectionMatrix();
	}
	
	//�r���[�s����擾
	const CMatrix& GetSpringViewMatrix()
	{
		return m_camera.GetViewMatrix();
	}

private:

	/*
	���݂̍��W����ڕW�̍��W�܂Ńo�l�v�Z���������ʂ����߂�
	positionNow		���݂̍��W
	positionTarget	�ڕW�̍��W
	moveSpeed		�ړ����x
	maxMoveSpeed	�ő呬�x
	danpingRate		������
	ret				�v�Z��̍��W
	*/
	CVector3 CalcSpringVector(const CVector3& positionNow, const CVector3& positionTarget, CVector3& moveSpeed, float maxMoveSpeed, float dampingRate);

	/*
	�����������߂�
	positionNow		���݂̌�����
	positionTarget	�ڕW�̌�����
	moveSpeed		�����x
	ret�@			�v�Z��̌�����
	*/
	float CalcSpringScalar(float positionNow, float positionTarget, float& moveSpeed);

	

private:
	CCamera			m_camera;				//�J����
	CVector3		m_target;				//�����_
	CVector3		m_position;				//���W
	CVector3		m_targetMoveSpeed;		//���݂̒����_����ڕW�̒����X�܂ł̈ړ����x
	CVector3		m_positionMoveSpeed;	//���݂̍��W����ڕW�̍��W�܂ł̈ړ����x
	float			m_maxMoveSpeed;			//�o�l�J�����̍ő呬�x
	float			m_targetDampingRate;	//�ڕW�̌�����
	float			m_dampingRate;			//���݂̌�����
	float			m_dampingRateVel;		//�������̉����x
	const float		m_dampingK;				//�������̌W��
};