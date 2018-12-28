#pragma once

class CShakeCamera
{
public:
	/*
	������
	position		�J�����̍��W
	target			�J�����̒����_
	shakeDirection	�h�����
	shakePower		�h��̋���
	*/
	void Init(const CVector3& position, const CVector3& target, const CVector3& shakeDirection, float shakePower);


	//const CVector3& GetPosition() const
	//{
	//	return m_position;
	//}

	//const CVector3& GetTarget() const
	//{
	//	return m_target;
	//}

	const CVector3& GetTarPosition() const
	{
		return m_tarPosition;
	}

	const CVector3& GetTarTarget() const
	{
		return m_tarTarget;
	}
	//�X�V
	void Update();

	//�h��̋�����ݒ�
	void SetShakeDirection(const CVector3& shakeDirection)
	{
		m_shakeDirection = shakeDirection;
	}
private:
	CVector3	m_position;
	CVector3	m_target;
	CVector3	m_tarTarget;
	CVector3	m_tarPosition;
	CVector3	m_shakeDirection;
	float		m_shakePower;

};