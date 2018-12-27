#pragma once
class ICollider;

//���̏��
struct SRigidBodyInfo
{
	SRigidBodyInfo()
	{
		collider = nullptr;
		mass = 0.0f;
		pos = { 0.0f, 0.0f, 0.0f };
		rot = { 0.0f, 0.0f, 0.0f, 1.0f };
	}
	CVector3 pos;			//���W
	CQuaternion rot;			//��]
	const ICollider* collider;		//�R���C�_�[
	float mass;					//���ʁA�����Ȃ����̂�0.0f�ł���
};

//���̂̃N���X
class CRigidBody : Uncopyable
{
public:
	//�R���X�g���N�^
	CRigidBody() :
		m_myMotionState(nullptr),
		m_rigidBody(nullptr)
	{

	}

	//�f�X�g���N�^
	~CRigidBody()
	{
		Release();
	}

	/*
	�������֐�
	rbInfo.pos		���W(Vector3)
	rbInfo.rot		��](Quaternion)
	rbInfo.collider	�R���C�_�[(ICollider*)
	mass			����(float)
	*/
	void Create(const SRigidBodyInfo& rbInfo);

	//�����[�X�֐�
	void Release();

	//���̂��擾
	const btRigidBody* GetBody() const
	{
		return m_rigidBody.get();
	}

	//���W��ݒ�
	void SetPosition(const CVector3& position)
	{
		m_rigidBody->getOneBeforeWorldTransform().setOrigin(m_rigidBody->getWorldTransform().getOrigin());
		m_rigidBody->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	}

	//���W���擾
	CVector3 GetPosition() const
	{
		CVector3 position ;
		btVector3 btPos = m_rigidBody->getWorldTransform().getOrigin();
		position.x = btPos.x();
		position.y = btPos.y();
		position.z = btPos.z();
		return position;
	}


	//���W���擾
	CQuaternion GetRotation() const
	{
		CQuaternion rotation;
		btQuaternion btRot = m_rigidBody->getWorldTransform().getRotation();
		rotation.x = btRot.x();
		rotation.y = btRot.y();
		rotation.z = btRot.z();
		rotation.w = btRot.w();
		return rotation;
	}

	//��]��ݒ�
	void SetRotation(const CQuaternion& rotation)
	{
		m_rigidBody->getOneBeforeWorldTransform().setRotation(m_rigidBody->getWorldTransform().getRotation());
		m_rigidBody->getWorldTransform().setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
	}

	//���̂�`��
	void Draw();

	//�������[���h�ɍ��̂�o�^
	void PhysicsWorldAddRigidBody();

	//�������[���h�ɍ��̂����X�g���O��
	void PhysicsWorldRemoveRigidBody();

	//���[�U�[�C���f�b�N�X��ݒ�
	void SetUserIndex(int index)
	{
		m_rigidBody->setUserIndex(index);
	}

	//�R���W�����t���O��ݒ�
	void SetCollisionFlags(int flag)
	{
		m_rigidBody->setCollisionFlags(flag);
	}

	//�A�N�e�B�x�[�V�����X�e�[�g��ݒ�
	void SetActivationState(int state)
	{
		m_rigidBody->setActivationState(state);
	}

	
	//void SetPlayerCollisionWallFlg(bool flg)
	//{
	//	m_rigidBody->setPlayerCollisionWallFlg(flg);
	//}

	//void SetPlayerCollisionGroundFlg(bool flg)
	//{
	//	m_rigidBody->setPlayerCollisionGroundFlg(flg);
	//}


private:
	std::unique_ptr<btDefaultMotionState>	m_myMotionState;		//���[�V�����X�e�C�g
	std::unique_ptr<btRigidBody>			m_rigidBody;			//����
};
