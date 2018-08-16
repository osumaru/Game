#include "engineStdafx.h"
#include "RigidBody.h"
#include "../Engine.h"
#include "CollisionAttr.h"
#include "Collider\ICollider.h"
#include "Physics.h"


void RigidBody::Create(const RigidBodyInfo& rbInfo)
{
	Release();

	m_myMotionState.reset(new btDefaultMotionState());
	btRigidBody::btRigidBodyConstructionInfo btRBInfo(rbInfo.mass, m_myMotionState.get(), const_cast<btCollisionShape*>(rbInfo.collider->GetBody()), btVector3(0, 0, 0));
	m_rigidBody.reset(new btRigidBody(btRBInfo));
	GetPhysicsWorld().AddRigidBody(m_rigidBody.get());
	SetPosition(rbInfo.pos);
	SetRotation(rbInfo.rot);
	m_rigidBody->getOneBeforeWorldTransform().setOrigin({ rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z });
	m_rigidBody->getOneBeforeWorldTransform().setRotation({ rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w });
	m_rigidBody->setUserIndex(enCollisionAttr_MapChip);
}

void RigidBody::PhysicsWorldAddRigidBody()
{
	GetPhysicsWorld().AddRigidBody(m_rigidBody.get());
}


void RigidBody::PhysicsWorldRemoveRigidBody()
{
	GetPhysicsWorld().RemoveRigidBody(m_rigidBody.get());
}

void RigidBody::Release()
{
	if (m_rigidBody)
	{
		GetPhysicsWorld().RemoveRigidBody(m_rigidBody.get());
		m_rigidBody.reset();
	}
}

void RigidBody::Draw()
{
	GetPhysicsWorld().DebugDraw(m_rigidBody->getWorldTransform(), m_rigidBody->getCollisionShape());
}