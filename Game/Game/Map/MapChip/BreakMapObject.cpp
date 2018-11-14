#include "stdafx.h"
#include "BreakMapObject.h"
#include "../../Enemy/Maw.h"

CBreakMapObject::CBreakMapObject():
	m_rigidBody(),
	m_boxCollider()
{
}

CBreakMapObject::~CBreakMapObject()
{
}

void CBreakMapObject::Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, const bool collider, CAnimation* anim)
{
	MapChip::Init(position, rotation, modelName, collider);

	SRigidBodyInfo rInfo;

	//���b�V���R���C�_�[����AABB���쐬
	/*if (!collider)
	{
		m_meshCollider.reset(new CMeshCollider);
		m_meshCollider->CreateCollider(&m_skinModel);
		rInfo.collider = m_meshCollider.get();
	}
	else
	{*/
		CMeshCollider mesh;
		mesh.CreateCollider(&m_skinModel);
		CVector3 boxsize = (mesh.GetAabbMax() - mesh.GetAabbMin()) / 2.0f;		
		CVector3 pos = (mesh.GetAabbMax() + mesh.GetAabbMin()) / 2.0f;
		rInfo.pos = pos;
		m_boxCollider.reset(new CBoxCollider);
		m_boxCollider->Create({ boxsize.x,boxsize.y,boxsize.z });
		rInfo.collider = m_boxCollider.get();
	//}



	rInfo.mass = 0.0f;
	rInfo.pos += m_position;
	rInfo.rot = m_rotation;

	//���̂��쐬
	m_rigidBody.reset(new CRigidBody);
	m_rigidBody->Create(rInfo);
	m_skinModel.Update(m_position, m_rotation, m_scale);
	//m_boxCollider.get()->GetBody()->setUserIndex(m_boxCollider.get()->GetBody()->getUserIndex());
	//m_rigidBody.get()->SetCollisionFlags(m_rigidBody.get()->GetBody()->CF_KINEMATIC_OBJECT);
	m_rigidBody.get()->SetUserIndex(m_rigidBody.get()->GetBody()->CF_KINEMATIC_OBJECT);

}


void CBreakMapObject::Update()
{

	float killY = -50.0f;		//�����ʒu
	float fallinSpeed = 0.02f;	//�����鑬�x
	float breakMaxLength = 12.0f;//�ő�j�󋗗�

	//�U�����Ă�����
	//if (GetMaw().GetIsAttack())
	//{
		//����̃{�[���̍��W���擾
		CMatrix BossLeftHandMat = GetMaw().GetBoneMatrix(L"RightHand");
		CVector3 BossLeftHandPos;

		BossLeftHandPos.x =BossLeftHandMat.m[3][0];
		BossLeftHandPos.y =BossLeftHandMat.m[3][1];
		BossLeftHandPos.z =BossLeftHandMat.m[3][2];
		CVector3 distance = BossLeftHandPos - m_position;
		//distance.y+=5.0f;
		float BreakLength = distance.Length();
		//�r�ɓ������Ă����炩���Ă��Ȃ�������
		if (BreakLength < breakMaxLength && !m_isBreak)
		{
			this->MapChipDelete();
			//m_isBreak = true;
		}
	//}

	//���ɗ��Ƃ��Ă�������
	//if (m_isBreak) 
	//{
	//	m_position.y -= fallinSpeed;
	//	//killZ��艺�����������
	//	if (m_position.y < killY)
	//	{
	//		this->MapChipDelete();
	//	}
	//}
	
	
}

void CBreakMapObject::Draw()
{
	MapChip::Draw();
	m_rigidBody->Draw();
}