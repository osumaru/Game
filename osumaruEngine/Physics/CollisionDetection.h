#pragma once
#include "RigidBody.h"
//�����蔻������N���X

class CCollisionDetection
{
public:

	//�R���X�g���N�^
	CCollisionDetection();

	//�f�X�g���N�^
	~CCollisionDetection();

	/*
	�������֐�
	colldier	�R���C�_�[
	position	���W
	rotation	��]
	*/
	void Init(const ICollider* collider, const CVector3& position, const CQuaternion& rotation);

	/*
	���W��ݒ�
	*/
	void SetPosition(const CVector3& position)
	{
		m_position = position;
		m_rigidBody.SetPosition(position);
	}

	/*
	��]��ݒ�
	*/
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
		m_rigidBody.SetRotation(m_rotation);
	}

	//���s
	void Execute();

	/*
	�������Ă邩�H
	true�Ȃ瓖�����Ă�Bfalse�Ȃ瓖�����ĂȂ�
	*/
	bool IsHit() const
	{
		return m_isHit;
	}

	/*
	UserIndex�̐ݒ�
	userIndex�@		�ݒ肵����UserIndex�̔ԍ�
	*/
	void SetUserIndex(int userIndex)
	{
		m_rigidBody.SetUserIndex(userIndex);
	}

	//���������I�u�W�F�N�g�̖@�����擾
	const CVector3& GetCollisionNormal() const
	{
		return m_hitCollisionNormal;
	}

	//��]���擾
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	//���W���擾
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//�q�b�g�����R���W�����̑������擾
	int GetHitCollisionType() const
	{
		return m_collisionType;
	}

	//���̃R���W�����̑�����ݒ�
	void SetJudgmentType(int judgmentType)
	{
		m_judgmentType = judgmentType;
	}
private:
	CRigidBody				m_rigidBody;			//����
	const ICollider*		m_pCollider;			//�R���C�_�[
	CVector3				m_position;				//���W
	CQuaternion				m_rotation;				//��]
	bool					m_isHit;				//�������Ă邩�H
	CVector3				m_hitCollisionNormal;	//�e�X�g�p
	int						m_collisionType;		//�q�b�g�����ؼޮ݂̑���
	int						m_judgmentType;			//���̃R���W�����̑���
};