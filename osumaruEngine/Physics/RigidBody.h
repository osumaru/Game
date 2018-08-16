#pragma once
class ICollider;

//���̏��
struct RigidBodyInfo
{
	RigidBodyInfo()
	{
		collider = nullptr;
		mass = 0.0f;
		pos = { 0.0f, 0.0f, 0.0f };
		rot = { 0.0f, 0.0f, 0.0f, 1.0f };
	}
	Vector3 pos;			//���W
	Quaternion rot;			//��]
	const ICollider* collider;		//�R���C�_�[
	float mass;					//���ʁA�����Ȃ����̂�0.0f�ł���
};

//���̂̃N���X
class RigidBody : Uncopyable
{
public:
	//�R���X�g���N�^
	RigidBody() :
		m_myMotionState(nullptr),
		m_rigidBody(nullptr)
	{

	}

	//�f�X�g���N�^
	~RigidBody()
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
	void Create(const RigidBodyInfo& rbInfo);

	//�����[�X�֐�
	void Release();

	//���̂��擾
	const btRigidBody* GetBody() const
	{
		return m_rigidBody.get();
	}

	//���W��ݒ�
	void SetPosition(Vector3 position)
	{
		m_rigidBody->getOneBeforeWorldTransform().setOrigin(m_rigidBody->getWorldTransform().getOrigin());
		m_rigidBody->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	}

	//��]��ݒ�
	void SetRotation(Quaternion rotation)
	{
		m_rigidBody->getOneBeforeWorldTransform().setRotation(m_rigidBody->getWorldTransform().getRotation());
		m_rigidBody->getWorldTransform().setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
	}

	void Draw();

	void PhysicsWorldAddRigidBody();

	void PhysicsWorldRemoveRigidBody();


	void SetUserIndex(int index)
	{
		m_rigidBody->setUserIndex(index);
	}

	void SetCollisionFlags(int flag)
	{
		m_rigidBody->setCollisionFlags(flag);
	}

	void SetActivationState(int state)
	{
		m_rigidBody->setActivationState(state);
	}

	void SetPlayerCollisionWallFlg(bool flg)
	{
		m_rigidBody->setPlayerCollisionWallFlg(flg);
	}

	void SetPlayerCollisionGroundFlg(bool flg)
	{
		m_rigidBody->setPlayerCollisionGroundFlg(flg);
	}


private:
	std::unique_ptr<btDefaultMotionState>	m_myMotionState;		//���[�V�����X�e�C�g
	std::unique_ptr<btRigidBody>			m_rigidBody;			//����
};
