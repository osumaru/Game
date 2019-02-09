#include "stdafx.h"
#include "Castle.h"
#include "../../Player/Player.h"
#include "../../Player/WireAction.h"
#include "../../Enemy/PathFinding/PathFinding.h"


void CCastle::Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, CAnimation* anim)
{
	MapChip::Init(position, rotation, modelName);

	SRigidBodyInfo rInfo;
	//	m_isTree = istree;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;
	CQuaternion multi = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, -90.0f);
	rInfo.rot.Multiply(multi);
	CMatrix rotMat;
	rotMat.MakeRotationFromQuaternion(m_rotation);
	m_meshCollider = std::make_unique<CMeshCollider>();
	m_meshCollider->CreateCollider(&m_skinModel);
	CVector3 boxsize = (m_meshCollider->GetAabbMax() - m_meshCollider->GetAabbMin()) / 2.0f;
	CVector3 pos = (m_meshCollider->GetAabbMax() + m_meshCollider->GetAabbMin()) / 2.0f;
	pos.Mul(rotMat);
	boxsize.x *= 0.1;
	boxsize.z *= 0.1;
	rInfo.collider = m_meshCollider.get();
	m_skinModel.SetIsAlphaTest(true);
	//„‘Ì‚ðì¬
	m_rigidBody.reset(new CRigidBody);
	m_rigidBody->Create(rInfo);
	GetPlayer().GetWireAction().Add(m_skinModel);
	m_skinModel.Update(m_position, m_rotation, m_scale, true);
	this->SetIsActive(true);
}


void CCastle::Update()
{
	MapChip::Update();
}

void CCastle::Draw()
{
	MapChip::Draw();
}