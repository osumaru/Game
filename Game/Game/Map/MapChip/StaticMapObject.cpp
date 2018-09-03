#include "stdafx.h"
#include "StaticMapObject.h"

StaticMapObject::StaticMapObject() :
	m_rigidBody(),
	m_boxCollider()
{

}

StaticMapObject::~StaticMapObject()
{

}

void StaticMapObject::Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, CAnimation* anim)
{
	MapChip::Init(position, rotation, modelName);

	//メッシュコライダーからAABBを作成
	m_boxCollider.reset(new CMeshCollider);
	m_boxCollider->CreateCollider(&m_skinModel);
	SRigidBodyInfo rInfo;
	rInfo.collider = m_boxCollider.get();
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;

	//剛体を作成
	m_rigidBody.reset(new CRigidBody);
	m_rigidBody->Create(rInfo);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	//m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
}


void StaticMapObject::Update()
{
	MapChip::Update();
	//m_skinModel.Update(m_position, m_rotation, m_scale);
}

void StaticMapObject::Draw()
{
	MapChip::Draw();
	//GetPhysicsWorld().DebugDraw(m_rigidBody->GetBody()->getWorldTransform(), m_rigidBody->GetBody()->getCollisionShape());
}