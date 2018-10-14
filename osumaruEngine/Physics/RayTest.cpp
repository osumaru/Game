#include "engineStdafx.h"
#include "RayTest.h"
#include "CollisionAttr.h"
#include "../Engine.h"
#include "Physics.h"

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

CRayTest::CRayTest()
{
}

CRayTest::~CRayTest()
{
}

void CRayTest::Init(float radius, float height)
{
	m_radius = radius;
	m_height = height;
	m_collider.Create(m_radius / 2.0f, m_height / 2.0f);
}

bool CRayTest::Execute(const CVector3 & position, const CVector3 target)
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

	CVector3 targetPos = target;
	targetPos.y += m_height * 0.5f + m_radius + 0.2f;

	//レイを作成する
	btTransform btStart, btEnd;
	btStart.setIdentity();
	btEnd.setIdentity();
	btStart.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
	btEnd.setOrigin(btVector3(targetPos.x, targetPos.y, targetPos.z));

	SConvexSweepCallBack callback;
	PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
	if (callback.isHit) {
		return true;
	}
	return false;
}
