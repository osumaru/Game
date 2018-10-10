#include "stdafx.h"
#include "WireCollisionSolver.h"
#include "../../../osumaruEngine/Physics/CollisionAttr.h"
#include "../../../osumaruEngine/Physics/Physics.h"
#include "../../../osumaruEngine/Engine.h"

struct SConvexSweepCallBack : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;

	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character) 
		{
			return 0.0f;
		}

		if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_MapChip)
		{
			isHit = true;
		}
		return 0.0f;
	}
};

CWireCollisionSolver::CWireCollisionSolver()
{
}

CWireCollisionSolver::~CWireCollisionSolver()
{
}

void CWireCollisionSolver::Init(float radius, float height)
{
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);
}

bool CWireCollisionSolver::Execute(const CVector3 & position, const CVector3 target)
{
	CVector3 vWK;
	vWK.Subtract(target, position);
	if (vWK.LengthSq() < FLT_EPSILON)
	{
		//���݂̍��W�ƈړ��悪�قړ������W�ɂ���
		return true;
	}

	//�J�v�Z���R���C�_�[�̒��S���W + 0.2f�̍��W�����߂�
	CVector3 posTmp = position;
	posTmp.y += m_height * 0.5f + m_radius + 0.2f;

	//���C���쐬����
	btTransform btStart, btEnd;
	btStart.setIdentity();
	btEnd.setIdentity();
	btStart.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
	btEnd.setOrigin(btVector3(target.x, posTmp.y, target.z));

	SConvexSweepCallBack callback;
	Engine().PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
	if (callback.isHit) {
		return true;
	}
	return false;
}
