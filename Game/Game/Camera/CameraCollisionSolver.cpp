#include "CameraCollisionSolver.h"

struct SConvexSweepCallback : public btCollisionWorld::ClosestConvexResultCallback
{
public:
	CVector3 m_rayDir;
	SConvexSweepCallback(CVector3 rayDir) :
		btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f)),
		m_rayDir(rayDir) {}
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		CVector3 normal;
		normal.x = convexResult.m_hitNormalLocal.x();
		normal.y = convexResult.m_hitNormalLocal.y();
		normal.z = convexResult.m_hitNormalLocal.z();

		if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character) {
			return 1.0f;
		}
		return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
	}
};

CCameraCollisionSolver::CCameraCollisionSolver()
{
}

CCameraCollisionSolver::~CCameraCollisionSolver()
{
}

void CCameraCollisionSolver::Init(float radius)
{
	m_radius = radius;
	m_collider.Create(radius);
}

bool CCameraCollisionSolver::Execute(CVector3& result, const CVector3& position, const CVector3& target)
{
	result = position;
	CVector3 vWk;
	vWk = target - position;
	if (vWk.LengthSq() < FLT_EPSILON)
	{
		//視点と注視点がほぼ同じ座標にある
		return false;
	}
	vWk.Normalize();
	//レイを作成する
	btTransform btStart, btEnd;
	btStart.setIdentity();
	btEnd.setIdentity();
	btStart.setOrigin(btVector3(target.x, target.y, target.z));
	btEnd.setOrigin(btVector3(position.x, position.y, position.z));
	SConvexSweepCallback callback(vWk);
	PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
	if (callback.hasHit()) {
		CVector3 vHitPos;
		vHitPos.x = callback.m_hitPointWorld.x();
		vHitPos.y = callback.m_hitPointWorld.y();
		vHitPos.z = callback.m_hitPointWorld.z();
		CVector3 vOffset;
		vOffset.x = callback.m_hitNormalWorld.x();
		vOffset.y = callback.m_hitNormalWorld.y();
		vOffset.z = callback.m_hitNormalWorld.z();
		vOffset *= m_radius;
		result = vHitPos + vOffset;
		return true;
	}
	return false;
}