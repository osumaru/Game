#include "stdafx.h"
#include "NormalShop.h"


CNormalShop::CNormalShop()
{
}


CNormalShop::~CNormalShop()
{
}

void CNormalShop::Init(const CVector3 position, const CQuaternion rotation, EShop shopType)
{
	m_shopType = shopType;
	m_position = position;
	m_rotation = rotation;
	wchar_t* animClip[] = { L"Assets/modelData/ShopgirlStand.tka" };
	m_animation.Init(animClip, 1);
	m_animation.SetLoopFlg(0, true);
	m_skinmodelNpc.Load(L"Assets/modelData/Shopgirl.cmo", &m_animation);
	m_animation.Play(0);
	m_skinModel.Load(L"Assets/modelData/roten3.cmo", NULL);
	m_skinModel.Update(m_position, m_rotation, m_scale, false);

	SRigidBodyInfo rInfo;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;
	CQuaternion multi = CQuaternion::Identity;
	rInfo.rot.Multiply(multi);
	//AABB�̍쐬
	{
		CMatrix rotMat;
		rotMat.MakeRotationFromQuaternion(multi);
		CMeshCollider mesh;
		mesh.CreateCollider(&m_skinModel);
		CVector3 boxsize = (mesh.GetAabbMax() - mesh.GetAabbMin()) / 2.0f;
		CVector3 pos = (mesh.GetAabbMax() + mesh.GetAabbMin()) / 2.0f;
		pos.Mul(rotMat);
		rInfo.pos = pos + m_position;
		m_boxCollider.reset(new CBoxCollider);
		m_boxCollider->Create({ boxsize.x,boxsize.y,boxsize.z });
		rInfo.collider = m_boxCollider.get();
		m_rigidBody.reset(new CRigidBody);
		m_rigidBody->Create(rInfo);
	}
}

void CNormalShop::Update()
{
	m_animation.Update(GameTime().GetDeltaFrameTime());
	m_skinModel.Update(m_position, m_rotation, m_scale, false);
	m_skinmodelNpc.Update(m_position, m_rotation, m_scale, true);
}

void CNormalShop::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	m_skinmodelNpc.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
