#include "engineStdafx.h"
#include "RigidBody.h"
#include "../Engine.h"
#include "CollisionAttr.h"
#include "Collider\ICollider.h"
#include "Physics.h"


void CRigidBody::Create(const SRigidBodyInfo& rbInfo)
{
	Release();

	m_myMotionState.reset(new btDefaultMotionState());
	btRigidBody::btRigidBodyConstructionInfo btRBInfo(rbInfo.mass, m_myMotionState.get(), const_cast<btCollisionShape*>(rbInfo.collider->GetBody()), btVector3(0, 0, 0));
	m_rigidBody.reset(new btRigidBody(btRBInfo));
	PhysicsWorld().AddRigidBody(m_rigidBody.get());
	SetPosition(rbInfo.pos);
	SetRotation(rbInfo.rot);
	m_rigidBody->getOneBeforeWorldTransform().setOrigin({ rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z });
	m_rigidBody->getOneBeforeWorldTransform().setRotation({ rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w });
	m_rigidBody->setUserIndex(enCollisionAttr_MapChip);
}

void CRigidBody::PhysicsWorldAddRigidBody()
{
	PhysicsWorld().AddRigidBody(m_rigidBody.get());
}


void CRigidBody::PhysicsWorldRemoveRigidBody()
{
	PhysicsWorld().RemoveRigidBody(m_rigidBody.get());
}

void CRigidBody::Release()
{
	if (m_rigidBody)
	{
		PhysicsWorld().RemoveRigidBody(m_rigidBody.get());
		m_rigidBody.reset();
	}
}

void CRigidBody::Draw()
{
	PhysicsWorld().DebugDraw(m_rigidBody->getWorldTransform(), m_rigidBody->getCollisionShape());
}