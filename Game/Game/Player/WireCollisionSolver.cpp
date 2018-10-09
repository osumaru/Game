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
		//現在の座標と移動先がほぼ同じ座標にある
		return true;
	}

	//カプセルコライダーの中心座標 + 0.2fの座標を求める
	CVector3 posTmp = position;
	posTmp.y += m_height * 0.5f + m_radius + 0.2f;

	//レイを作成する
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
