#pragma once

class CShakeCamera
{
public:
	/*
	������
	position		�J�����̍��W
	target			�J�����̒����_
	shakeDirection	�h�����
	damping			������
	*/
	void Init(const CVector3& position, const CVector3& target, const CVector3& shakeDirection, float damping);

	/*
	�h��X�^�[�g
	shakePower	�h����
	*/
	void ShakeStart(float shakePower)
	{
		m_shakePower = shakePower;
	}

	//���W��ݒ�
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}

	//���W���擾
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//�����_��ݒ�
	void SetTarget(const CVector3& target)
	{
		m_target = target;
	}

	//�����_���擾
	const CVector3& GetTarget() const
	{
		return m_target;
	}

	//�h�ꂽ��̃J�����̍��W���擾
	const CVector3& GetShakePosition() const
	{
		return m_shakePosition;
	}

	//�h�ꂽ��̒����_���擾
	const CVector3& GetShakeTarget() const
	{
		return m_shakeTarget;
	}
	//�X�V
	void Update();

	//�h��̋�����ݒ�
	void SetShakeDirection(const CVector3& shakeDirection)
	{
		m_shakeDirection = shakeDirection;
	}

	//�x�����Ԃ�ݒ�
	void SetDelayTime(float delayTime)
	{
		m_delayTime = delayTime;
	}
	//�x�����Ă���t���[������ݒ�
	void SetDelayCount(int delayCount)
	{
		m_delayCount = delayCount;
	}

private:
	CVector3	m_position;			//�J�����̍��W
	CVector3	m_target;			//�����_�̍��W
	CVector3	m_shakeTarget;		//�h�ꂽ��̒����_
	CVector3	m_shakePosition;	//�h�ꂽ��̃J�����̍��W
	CVector3	m_shakeDirection;	//�h�����
	float		m_shakePower;		//�h����
	float		m_damping;			//�h��̌�����
	float		m_delayTime = 0.0f;	//�h��܂ł̒x������
	int			m_delayCount = 0;	//�h��܂ł̒x������t���[����
};