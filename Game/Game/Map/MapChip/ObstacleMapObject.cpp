#include "stdafx.h"
#include "ObstacleMapObject.h"
#include "../../Player/Player.h"
#include "../../Player/WireAction.h"
#include "../../Enemy/PathFinding/PathFinding.h"

CObstacleMapObject::CObstacleMapObject() :
	m_rigidBody(),
	m_boxCollider()
{
	this->SetIsActive(false);
}

CObstacleMapObject::~CObstacleMapObject()
{
}

void CObstacleMapObject::Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, const bool collider, CAnimation* anim)
{
	MapChip::Init(position, rotation, modelName, collider);

	SRigidBodyInfo rInfo;

	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;
	CQuaternion multi = CQuaternion::Identity;
	rInfo.rot.Multiply(multi);
	m_skinModel.Update(m_position, m_rotation, m_scale);

	CMatrix rotMat;
	rotMat.MakeRotationFromQuaternion(multi);
	CMeshCollider mesh;
	mesh.CreateCollider(&m_skinModel);
	CVector3 boxsize = (mesh.GetAabbMax() - mesh.GetAabbMin()) / 2.0f;
	boxsize.y += 2.0f;
	CVector3 pos = (mesh.GetAabbMax() + mesh.GetAabbMin()) / 2.0f;
	rInfo.pos = m_position;
	rInfo.pos.x += pos.x;
	rInfo.pos.z += pos.y; 
	rInfo.pos.y += pos.z;
	m_boxCollider.Create({ boxsize.x,boxsize.y,boxsize.z });
	rInfo.collider = &m_boxCollider;

	//„‘Ì‚ðì¬
	m_rigidBody.Create(rInfo);
	GetPlayer().GetWireAction().Add(m_skinModel);
	this->SetIsActive(true);
	CNavigationMesh::SObstacleInfo naviInfo;
	naviInfo.aabbMax = mesh.GetAabbMax();
	naviInfo.aabbMin = mesh.GetAabbMin();
	naviInfo.center = m_position;
	g_pathFinding.GetNavigationMesh().AddObstacleObject(naviInfo);

}


void CObstacleMapObject::Update()
{
	MapChip::Update();
}

void CObstacleMapObject::Draw()
{
	MapChip::Draw();
	m_rigidBody.Draw();
}