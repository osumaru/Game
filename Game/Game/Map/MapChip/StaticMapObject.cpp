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

void StaticMapObject::Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, const bool collider, CAnimation* anim)
{
	MapChip::Init(position, rotation, modelName,collider);

	SRigidBodyInfo rInfo;
	
	//メッシュコライダーからAABBを作成
	if (!collider)
	{
		m_meshCollider.reset(new CMeshCollider);
		m_meshCollider->CreateCollider(&m_skinModel);
		rInfo.collider = m_meshCollider.get();
	}
	else
	{
		CMeshCollider mesh;
		mesh.CreateCollider(&m_skinModel);
		CVector3 boxsize = (mesh.GetAabbMax() - mesh.GetAabbMin());
		boxsize.x /= 2.0f;
		boxsize.z /= 2.0f;
		m_boxCollider.reset(new CBoxCollider);
		m_boxCollider->Create({ boxsize.x,boxsize.y,boxsize.z });
		rInfo.collider = m_boxCollider.get();
	}


	
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