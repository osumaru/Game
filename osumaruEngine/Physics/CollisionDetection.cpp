#include "engineStdafx.h"
#include "CollisionDetection.h"
#include "../Engine.h"
#include "CollisionAttr.h"
#include "Physics.h"

struct ContactSingle : public btCollisionWorld::ContactResultCallback
{
	bool isHit = false;
	CVector3 hitObjectNormal;
	const btCollisionObject* me = nullptr;				//自分自身。自分自身との衝突を除外するためのメンバ。
	int collisionType = enCollisionAttr_Unknown;
	int judgmentType = enJudgment_Wall;

	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)override
	{
		isHit = true;

		CQuaternion quaternion;
		btQuaternion btRot = colObj1Wrap->getCollisionObject()->getWorldTransform().getRotation();
		quaternion.x = btRot.x();
		quaternion.y = btRot.y();
		quaternion.z = btRot.z();
		quaternion.w = btRot.w();
		CMatrix rot;
		rot.MakeRotationFromQuaternion(quaternion);
		//法線を取得
		hitObjectNormal.x = cp.m_normalWorldOnB.x();
		hitObjectNormal.y = cp.m_normalWorldOnB.y();
		hitObjectNormal.z = cp.m_normalWorldOnB.z();
		collisionType = colObj1Wrap->getCollisionObject()->getUserIndex();
		//当たっていたのがキャラクターじゃない場合フラグを立てる
		if (collisionType != enCollisionAttr_Character)
		{
			switch (judgmentType)
			{
			case enJudgment_Ground:
				const_cast<btCollisionObject*>(colObj1Wrap->getCollisionObject())->setPlayerCollisionGroundFlg(true);
				break;
			case enJudgment_Wall:
				const_cast<btCollisionObject*>(colObj1Wrap->getCollisionObject())->setPlayerCollisionWallFlg(true);
				break;
			default:
				break;
			}
		}
		return 0.0f;
	}
};

CCollisionDetection::CCollisionDetection() :
	m_rigidBody(),
	m_pCollider(nullptr),
	m_position(0.0f, 0.0f, 0.0f),
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_isHit(false),
	m_hitCollisionNormal(0.0f, 0.0f, 0.0f),
	m_collisionType(0),
	m_judgmentType(0)
{
}

CCollisionDetection::~CCollisionDetection()
{
	m_rigidBody.Release();
}

void CCollisionDetection::Init(const ICollider* collider, const CVector3& position, const CQuaternion& rotation)
{

	//剛体を初期化
	SRigidBodyInfo rbInfo;
	m_pCollider = collider;
	m_position = position;
	m_rotation = rotation;
	rbInfo.collider = collider;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	m_rigidBody.SetActivationState(DISABLE_DEACTIVATION);
	m_rigidBody.SetUserIndex(enCollisionAttr_Detection);
}

void CCollisionDetection::Execute()
{
	//collisionWorldと剛体の個別の衝突テスト
	ContactSingle callBack;
	callBack.me = m_rigidBody.GetBody();
	callBack.judgmentType = m_judgmentType;
	PhysicsWorld().ContactTest(m_rigidBody.GetBody(), callBack);
	m_isHit = callBack.isHit;
	m_collisionType = callBack.collisionType;
	m_hitCollisionNormal = callBack.hitObjectNormal;
}
