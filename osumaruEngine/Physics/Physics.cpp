#include "engineStdafx.h"
#include "Physics.h"
#include "RigidBody.h"
#include "RigidBodyDraw.h"
#include "../Camera/Camera.h"
#include "../Timer/GameTime.h"

CPhysicsWorld::CPhysicsWorld() :
	m_pCollisionConfig(nullptr),
	m_pCollisionDispatcher(nullptr),
	m_pOverlappingPairCache(nullptr),
	m_pConstraintSolver(nullptr),
	m_pDynamicWorld(nullptr),
	m_pRigidBodyDraw(nullptr),
	m_pCamera(nullptr)
{
}

CPhysicsWorld::~CPhysicsWorld()
{
}


void CPhysicsWorld::Init()
{
	//�����G���W����������
	m_pCollisionConfig.reset(new btDefaultCollisionConfiguration);
	m_pCollisionDispatcher.reset(new btCollisionDispatcher(m_pCollisionConfig.get()));
	m_pOverlappingPairCache.reset(new btDbvtBroadphase());
	m_pConstraintSolver.reset(new btSequentialImpulseConstraintSolver());

	m_pDynamicWorld.reset(new btDiscreteDynamicsWorld(
		m_pCollisionDispatcher.get(),
		m_pOverlappingPairCache.get(),
		m_pConstraintSolver.get(),
		m_pCollisionConfig.get()
	));
	m_pDynamicWorld->setGravity(btVector3(0, -10, 0));
	m_pRigidBodyDraw.reset(new CRigidBodyDraw);
	m_pRigidBodyDraw->Init();
	m_pDynamicWorld->setDebugDrawer(m_pRigidBodyDraw.get());
}

void CPhysicsWorld::Update()
{
	m_pDynamicWorld->stepSimulation(GameTime().GetDeltaFrameTime());
}

void CPhysicsWorld::Draw()
{
#ifdef _DEBUG
	if (m_pCamera != nullptr)
	{
		m_pRigidBodyDraw->Draw(m_pCamera->GetViewMatrix(), m_pCamera->GetProjectionMatrix());
		m_pRigidBodyDraw->Reset();
	}
#endif
}

void CPhysicsWorld::AddRigidBody(btRigidBody* rb)
{
	m_pDynamicWorld->addRigidBody(rb);
}

void CPhysicsWorld::RemoveRigidBody(btRigidBody* rb)
{
	m_pDynamicWorld->removeRigidBody(rb);
}