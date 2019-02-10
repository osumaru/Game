#include "Tree.h"
#include "../../Player/Player.h"
#include "../../Player/WireAction.h"
#include "../../Enemy/PathFinding/PathFinding.h"


void CTree::Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, CAnimation* anim)
{
	MapChip::Init(position, rotation, modelName);

	SRigidBodyInfo rInfo;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;
	CMatrix rotMat;
	rotMat.MakeRotationFromQuaternion(m_rotation);
	CMeshCollider mesh;
	mesh.CreateCollider(&m_skinModel);
	CVector3 boxsize = (mesh.GetAabbMax() - mesh.GetAabbMin()) / 2.0f;
	CVector3 pos = (mesh.GetAabbMax() + mesh.GetAabbMin()) / 2.0f;
	pos.Mul(rotMat);
	boxsize.x *= 0.1;
	boxsize.z *= 0.1;
	rInfo.pos = pos + m_position;
	m_boxCollider.reset(new CBoxCollider);
	m_boxCollider->Create({ boxsize.x,boxsize.y,boxsize.z });
	rInfo.collider = m_boxCollider.get();
	m_skinModel.SetIsAlphaTest(true);
	//„‘Ì‚ðì¬
	m_rigidBody.reset(new CRigidBody);
	m_rigidBody->Create(rInfo);
	GetPlayer().GetWireAction().Add(m_skinModel);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	this->SetIsActive(true);
}


void CTree::Update()
{
	MapChip::Update();
}

void CTree::Draw()
{
	MapChip::Draw();
	m_rigidBody->Draw();
}