#pragma once

#include "Collider\CapsuleCollider.h"
#include "RigidBody.h"


const float cPI = 3.14159265358979323846f;

//�L�����N�^�[�R���g���[���[
//�Փˉ����ƏՓ˔�������Ă����N���X�B

class CCharacterController
{
public:
	//�R���X�g���N�^
	CCharacterController();

	//�f�X�g���N�^
	~CCharacterController();

	/*
	�������֐�
	float		radius		�L�����N�^�[�̔��a�@�@�@
	float		height		�L�����N�^�[�̍����@
	Vector3 position	�L�����̍��W

	�R���C�_�[�̓J�v�Z���R���C�_�[�ŃL�����N�^�[�̌��_�������ɂ��邱�Ƃ�O��Ƃ��Ă���B
	*/
	void Init(float radius, float height, const CVector3& position);

	//���s�֐�
	void Execute(float deltaTime);

	//�����Ă�I�u�W�F�N�g�Ƃ̂����蔻����Ƃ�
	void StaticExecute();

	//���W���擾�B
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//���W��ݒ�B
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	//�ړ����x��ݒ�B
	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_moveSpeed = moveSpeed;
		//������Ɉړ����x���^�����Ă����ꍇ�W�����v����Ƃ݂Ȃ�
		if (m_moveSpeed.y > 0.0f)
		{
			Jump();
		}
	}
	
	//�ړ����x���擾�B
	const CVector3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}

	//�W�����v����Ƃ��ɌĂ΂��֐��B
	void Jump()
	{
		m_isJump = true;
		m_isOnGround = false;
	}

	//�W�����v���Ă��邩�H
	bool IsJump() const
	{
		return m_isJump;
	}

	//�n�ʂɐڒn���Ă��邩�H
	bool IsOnGround() const
	{
		return m_isOnGround;
	}

	//�R���C�_�[���擾�B
	const CCapsuleCollider* GetCollider() const
	{
		return &m_collider;
	}

	//�d�͂�ݒ�B
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}

	//�d�͂��擾
	float GetGravity() const
	{
		return m_gravity;
	}

	//���̂��폜�B
	void RemovedRigidBody();

	//�������Ă���n�ʂ̃I�u�W�F�N�g���擾
	const btCollisionObject* GetGroundCollisionObject() const
	{
		return m_groundHitObject;
	}

	//�������Ă���ǂ̃I�u�W�F�N�g���擾
	const btCollisionObject* GetWallCollisionObject() const
	{
		return m_wallHitObject;
	}

	//�ǂ̖@�����擾
	const CVector3& GetWallNormal() const
	{
		return m_wallNormal;
	}

	//���[�U�[�C���f�b�N�X��ݒ�
	void SetUserIndex(int userNum)
	{
		m_rigidBody.SetUserIndex(userNum);
	}

	//�␳�l�̐ݒ�
	void SetRigidBodyManip(float RigidBodyManip)
	{
		m_rigidBodyManip = RigidBodyManip;
	}

	//���̂�`��
	void Draw();

	//�����ɓ����������̃t���O��Ԃ�
	bool IsHit() const
	{
		if (m_wallHitObject != nullptr || m_groundHitObject != nullptr)
		{
			return true;
		}
		return false;
	}

private:
	CVector3					m_position;				//���W
	CVector3					m_moveSpeed;			//�ړ����x
	bool						m_isJump;				//�W�����v���Ă��邩�H
	bool						m_isOnGround;			//�n�ʂɐݒu���Ă��邩�H
	CCapsuleCollider			m_collider;				//�R���C�_�[
	float						m_radius;				//���a
	float						m_height;				//����
	CRigidBody					m_rigidBody;			//����
	float						m_gravity;				//�d��
	const btCollisionObject*	m_groundHitObject;		//�������Ă���n�ʂ̃I�u�W�F�N�g
	const btCollisionObject*	m_wallHitObject;		//�������Ă���ǂ̃I�u�W�F�N�g
	CVector3					m_wallNormal;			//���������ǂ̖@��
	float						m_rigidBodyManip;		//�␳�l�i���͎g���ĂȂ�
};