#include "stdafx.h"
#include "StaticMapObject.h"
#include "../../Player/Player.h"
#include "../../Player/WireAction.h"
#include "../../Enemy/PathFinding/PathFinding.h"

StaticMapObject::StaticMapObject() :
	m_rigidBody()
{
	this->SetIsActive(false);
}

StaticMapObject::~StaticMapObject()
{
}

void StaticMapObject::Init(const SMapChipInfo& info, CAnimation* anim)
{
	MapChip::Init(info);

	SRigidBodyInfo rInfo;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;
	m_skinModel.Update(m_position, m_rotation, m_scale);

	m_meshCollider.reset(new CMeshCollider);
	m_meshCollider->CreateCollider(&m_skinModel);
	rInfo.collider = m_meshCollider.get();
	
	//„‘Ì‚ðì¬
	m_rigidBody.reset(new CRigidBody);
	m_rigidBody->Create(rInfo);
	GetPlayer().GetWireAction().Add(m_skinModel);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	this->SetIsActive(true);
}


void StaticMapObject::Update()
{
	MapChip::Update();
}

void StaticMapObject::Draw()
{
	MapChip::Draw();
}