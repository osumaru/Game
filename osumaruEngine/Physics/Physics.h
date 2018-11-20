#pragma once
#pragma once
class CRigidBody;
class CRigidBodyDraw;
class CCamera;

/*
�������[���h
*/
class CPhysicsWorld : Uncopyable
{
	std::unique_ptr<btDefaultCollisionConfiguration>		m_pCollisionConfig;
	std::unique_ptr<btCollisionDispatcher>					m_pCollisionDispatcher;		//�Փˉ�������
	std::unique_ptr<btBroadphaseInterface>					m_pOverlappingPairCache;		//�u���[�h�t�F�[�Y�B
	std::unique_ptr<btSequentialImpulseConstraintSolver>	m_pConstraintSolver;			//�R���X�g���C���g�\���o�[�B�S�������̉�������
	std::unique_ptr<btDiscreteDynamicsWorld>				m_pDynamicWorld;				//���[���h
	std::unique_ptr<CRigidBodyDraw>							m_pRigidBodyDraw;
	CCamera*												m_pCamera;
public:
	//�R���X�g���N�^
	CPhysicsWorld();

	//�f�X�g���N�^
	~CPhysicsWorld();

	//�������֐�
	void Init();

	//�X�V�֐�
	void Update();

	void Draw();

	//�_�C�i�~�b�N���[���h���擾�B
	const btDiscreteDynamicsWorld* GetDynamicWorld() const
	{
		return m_pDynamicWorld.get();
	}
	//���̂𕨗����[���h�ɒǉ�
	void AddRigidBody(btRigidBody* rb);

	//���̂𕨗����[���h����폜
	void RemoveRigidBody(btRigidBody* rb);

	//���̕`��p�̃J������ݒ�
	void SetCamera(CCamera* camera)
	{
		m_pCamera = camera;
	}

	/*
	�������[���h�Ń��C���΂�
	castShape			����
	convexFromWorld		���C�̎n�_
	convexToWorld		���C�̏I�_
	resultCallback		�R�[���o�b�N
	*/
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f)
	{
		m_pDynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}

	/*
	�������[���h�ō��̂������ɓ������Ă邢���e�X�g
	collisionObject		����
	resultCallback		�R�[���o�b�N
	*/
	void ContactTest(
		const btCollisionObject* collisionObject,
		btCollisionWorld::ContactResultCallback& resultCallback)
	{
		m_pDynamicWorld->contactTest(const_cast<btCollisionObject*>(collisionObject), resultCallback);
	}

	/*
	���̂����C���`��
	worldTrans		���[���h�s��
	colShape		����
	*/
	void  DebugDraw(
		const btTransform& worldTrans,
		const btCollisionShape* colShape)
	{
#ifdef _DEBUG
		//m_pDynamicWorld->debugDrawObject(worldTrans, colShape, { 0.0f, 0.0f, 0.0f });
#endif
	}
};