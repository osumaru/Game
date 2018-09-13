#include "engineStdafx.h"
#include "CharacterController.h"
#include "Physics.h"
#include "CollisionAttr.h"
#include "../Engine.h"


//衝突したときに呼ばれる関数オブジェクト(地面用)
struct SSweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//衝突フラグ。
	CVector3 hitPos = { 0.0f, 0.0f, 0.0f };		//衝突点。
	CVector3 startPos = { 0.0f, 0.0f, 0.0f };	//レイの始点。
	CVector3 hitNormal = { 0.0f, 0.0f, 0.0f };	//衝突点の法線
	const btCollisionObject* hitObject = nullptr;
	const btCollisionObject* me = nullptr;				//自分自身。自分自身との衝突を除外するためのメンバ。
	float dist = FLT_MAX;							//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。
													//衝突したときに呼ばれるコールバック関数。
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Detection)
		{
			//自分に衝突した。orキャラクタ属性のコリジョンと衝突した。
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//衝突点の法線を引っ張ってくる
		CVector3	hitNormalTmp;
		hitNormalTmp.Set(convexResult.m_hitNormalLocal);
		//上方向と法線のなす角度を求める。
		CVector3 up = { 0.0f, 1.0f, 0.0f };
		float angle = hitNormalTmp.Dot(up);
		
		angle = fabsf(acosf(angle));
		if (angle < cPI * 0.3f ||		//地面の傾斜が54度より小さいので地面とみなす。角度がラジアン単位なので180度がcPI
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground)//もしくはコリジョン属性が地面と指定されている。
		{

			//衝突している。
			isHit = true;
			CVector3 hitPosTmp;
			hitPosTmp.Set(convexResult.m_hitPointLocal);
			//衝突点の距離を求める。
			CVector3 vDist;
			vDist = hitPosTmp - startPos;
			float distTmp = vDist.Length();
			if (dist > distTmp)
			{
				//この衝突点の方が近いので、最近傍の衝突点を更新する。
				hitPos = hitPosTmp;
				hitNormal.Set(convexResult.m_hitNormalLocal);
				dist = distTmp;
			}
		}
		return 0.0f;
	}
};

//衝突したときに呼ばれる関数オブジェクト(天井用)
struct SSweepResultCeiling : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//衝突フラグ。
	CVector3 hitPos = { 0.0f, 0.0f, 0.0f };		//衝突点。
	CVector3 startPos = { 0.0f, 0.0f, 0.0f };	//レイの始点。
	CVector3 hitNormal = { 0.0f, 0.0f, 0.0f };	//衝突点の法線
	const btCollisionObject* hitObject = nullptr;
	const btCollisionObject* me = nullptr;				//自分自身。自分自身との衝突を除外するためのメンバ。
	float dist = FLT_MAX;							//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。
													//衝突したときに呼ばれるコールバック関数。
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Detection)
		{
			//自分に衝突した。orキャラクタ属性のコリジョンと衝突した。
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//衝突点の法線を引っ張ってくる
		CVector3	hitNormalTmp;
		hitNormalTmp.Set(convexResult.m_hitNormalLocal);
		//下方向と法線のなす角度を求める。
		CVector3 up = { 0.0f, -1.0f, 0.0f };
		float angle = hitNormalTmp.Dot(up);
		angle = fabsf(acosf(angle));
		if (angle < cPI * 0.3f ||		//地面の傾斜が54度より小さいので地面とみなす。角度がラジアン単位なので180度がcPI
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground)//もしくはコリジョン属性が地面と指定されている。
		{
			//衝突している。
			isHit = true;
			CVector3 hitPosTmp;
			hitPosTmp.Set(convexResult.m_hitPointLocal);
			//衝突点の距離を求める。
			CVector3 vDist;
			vDist = hitPosTmp - startPos;
			float distTmp = vDist.Length();
			if (dist > distTmp)
			{
				//この衝突点の方が近いので、最近傍の衝突点を更新する。
				hitPos = hitPosTmp;
				hitNormal.Set(convexResult.m_hitNormalLocal);
				dist = distTmp;
			}
		}
		return 0.0f;
	}
};

//衝突したときに呼ばれる関数オブジェクト(壁用)
struct SSweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//衝突フラグ。
	CVector3 hitPos = { 0.0f, 0.0f, 0.0f };		//衝突点。
	CVector3 startPos = { 0.0f, 0.0f, 0.0f };	//レイの始点。
	CVector3 ray = { 0.0f, 0.0f, 0.0f };
	bool		isRay = false;
	float		distance = 0.0f;
	float dist = FLT_MAX;							//衝突点までの距離。一番近い衝突点を求めるため。FLT_MAXは単精度の浮動小数点が取りうる最大の値。
	CVector3	hitNormal = { 0.0f, 0.0f, 0.0f };	//衝突点の法線
	const btCollisionObject* me = NULL;					//自分自身。自分自身との衝突を除外するためのメンバ。
	const btCollisionObject* hitObject = NULL;
													//衝突したときに呼ばれるコールバック関数
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Detection)
		{
			//自分に衝突した。or地面に衝突した。
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//衝突点の法線を引っ張ってくる。
		CVector3 hitNormalTmp;
		hitNormalTmp.Set(convexResult.m_hitNormalLocal);
		//上方向と衝突点の法線のなす角度を求める
		CVector3 up = { 0.0f, 1.0f, 0.0f };
		float angle = hitNormalTmp.Dot(up);
		angle = fabsf(acosf(angle));
		if (angle >= cPI * 0.3f ||		//地面の傾斜が54度以上なので壁とみなす。
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character)//もしくはコリジョン属性がキャラクタなので壁とみなす。
		{
			ray.Normalize();
			btVector3 btMoveSpeed = hitObject->getWorldTransform().getOrigin() - hitObject->getOneBeforeWorldTransform().getOrigin();
			CVector3 moveSpeed = { btMoveSpeed.x(), btMoveSpeed.y(), btMoveSpeed.z() };
			distance = moveSpeed.Length();
			if (FLT_EPSILON <= distance)
			{
				moveSpeed.Normalize();
				if (ray.Dot(moveSpeed) < 0.0f)
				{
					isRay = true;
				}
			}
			isHit = true;
			CVector3 hitPosTmp;
			hitPosTmp.Set(convexResult.m_hitPointLocal);
			//交点との距離を調べる。
			CVector3 vDist;
			vDist = hitPosTmp - startPos;
			vDist.y = 0.0f;
			float distTmp = vDist.Length();
			if (distTmp < dist)
			{
				//この衝突点の方が近いので、最近傍の衝突点を更新する。
				hitPos = hitPosTmp;
				dist = distTmp;
				hitNormal = hitNormalTmp;
			}
		}
		return 0.0f;
	}
};

CCharacterController::CCharacterController() :
	m_position(0.0f, 0.0f, 0.0f),
	m_moveSpeed(0.0f, 0.0f, 0.0f),
	m_isJump(false),
	m_isOnGround(true),
	m_collider(),
	m_radius(0.0f),
	m_height(0.0f),
	m_rigidBody(),
	m_gravity(-9.8f),
	m_groundHitObject(nullptr),
	m_wallHitObject(nullptr),
	m_wallNormal(0.0f, 0.0f, 0.0f),
	m_rigidBodyManip(0.0f)
{
}

CCharacterController::~CCharacterController()
{
	RemovedRigidBody();
}

void CCharacterController::Init(float radius, float height, const CVector3& position)
{
	m_position = position;
	m_moveSpeed = {0.0f, 0.0f, 0.0f};
	//コリジョン作成。
	m_radius = radius;
	m_height = height;
	m_collider.Create(m_radius, m_height);

	//剛体を初期化。
	SRigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	//剛体の位置を更新。
	m_rigidBody.SetPosition(m_position);
	//@todo 未対応。 trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.SetUserIndex(enCollisionAttr_Character);
	m_rigidBody.SetCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
}

void CCharacterController::Execute(float deltaTime)
{
	//StaticExecute();
	CPhysicsWorld& physicsWorld = PhysicsWorld();
	//速度に重力加速度を加える。
	m_moveSpeed.y += m_gravity * deltaTime;
	//次の移動先となる座標を計算する。
	CVector3 nextPosition = m_position;
	//速度からこのフレームでの移動量を求める。オイラー積分。
	CVector3 addPos = m_moveSpeed;
	addPos *= deltaTime;
	nextPosition += addPos;
	CVector3 originalXZDir = addPos;
	originalXZDir.y = 0.0f;
	originalXZDir.Normalize();

	//XZ平面での衝突検出と衝突解決を行う。
	{
		int loopCount = 0;
		const btCollisionObject* wallCollisionObject = nullptr;
		CVector3 hitNormal = { 0.0f, 0.0f, 0.0f };
		while (true)
		{
			//現在の座標から次の移動先へ向かうベクトルを求める。
			CVector3  addPosXZ;
			addPosXZ = nextPosition - m_position;
			addPosXZ.y = 0.0f;
			if (addPosXZ.Length() < FLT_EPSILON)
			{
				//XZ平面で動きがないので調べる必要なし。
				//FLTEPSILONは1より大きい、最小の値との差分を表す定数。
				//とても小さい値のことです。
				break;
			}
			//カプセルコライダーの中心座標　+ 0.2の座標をposTmpに求める。
			CVector3 posTmp = m_position;
			posTmp.y += m_height * 0.5f + m_radius + 0.2f;
			//レイを作成。
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			//始点はカプセルコライダーの中心座標 + 0.2の座標をposTmpdに求める。
			start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
			//終点は次の移動先。XZ平面での衝突を調べるので、yはposTmp.yを設定する。
			end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

			SSweepResultWall callback;
			callback.me = m_rigidBody.GetBody();
			callback.startPos = posTmp;
			//衝突検出。
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			if (callback.isHit)
			{
				wallCollisionObject = callback.hitObject;
				//当たった。
				//壁。
				CVector3 vT0, vT1;
				//XZ平面での移動後の座標をvT0に、交点(衝突点)をvT1に設定する。
				vT0 = { nextPosition.x, 0.0f, nextPosition.z };
				vT1 = { callback.hitPos.x, 0.0f, callback.hitPos.z };
				//めり込みが発生している移動ベクトルを求める。
				CVector3 vMerikomi;
				vMerikomi = vT1 - vT0;

				//XZ平面での衝突した壁の法線を求める。
				CVector3 hitNormalXZ = callback.hitNormal;
				hitNormalXZ.y = 0.0f;
				hitNormalXZ.Normalize();
				hitNormal = hitNormalXZ;
				//めり込みベクトルを壁の法線に射影する。
				float fT0 = hitNormalXZ.Dot(vMerikomi);
				//押し戻し返すベクトルを求める。
				//押し返すベクトルは壁の法線に射影されためり込みベクトル。
				CVector3 vOffset;
				vOffset = hitNormalXZ;
				vOffset *= (fT0 + m_radius);//コライダーの半径分手動で戻している
				nextPosition += vOffset;
				CVector3 currentDir;
				currentDir = nextPosition - m_position;
				currentDir.y = 0.0f;
				currentDir.Normalize();
				if (currentDir.Dot(originalXZDir) < 0.0f)
				{
					//角に入った時のキャラクタの振動を防止するために、
					//移動先が逆向き
					nextPosition.x = m_position.x;
					nextPosition.z = m_position.z;
					break;
				}
			}
			else
			{
				//どことも当たらないので終わり。
				break;
			}
			m_wallHitObject = callback.hitObject;
			loopCount++;
			if (loopCount == 5)
			{
				break;
			}
			if (callback.hitObject != nullptr && m_rigidBody.GetBody()->getUserIndex() == enCollisionAttr_Character)
			{
				const_cast<btCollisionObject*>(callback.hitObject)->setPlayerCollisionWallFlg(true);
			}
		}
		m_wallNormal = hitNormal;
		m_wallHitObject = wallCollisionObject;
	}
	//XZの移動は確定。
	m_position.x = nextPosition.x;
	m_position.z = nextPosition.z;

	CVector3 addPosY;
	addPosY = nextPosition - m_position;
	//下方向を調べる。
	{
		m_position = nextPosition;	//移動の仮確定。
									//レイを作成する。
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//始点はカプセルコライダーの中心。
		start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		//終点は地面上にいない場合は1m下を見る。
		//地面上にいなくてジャンプで上昇中の場合は上昇量の0.01倍下を見る。
		//地面上にいなくて降下中の場合はそのまま落下先を調べる。
		CVector3 endPos;
		endPos.Set(start.getOrigin());
		if (!m_isOnGround)
		{
			if (addPosY.y > 0.0f)
			{
				//ジャンプ中とかで上昇中。
				//上昇中でもXZに移動した結果めり込んでいる可能性があるので下を調べる。
				endPos.y -= addPosY.y * 0.01f;
			}
			else
			{
				endPos.y += addPosY.y;
			}
		}
		else
		{
			//地面上にいる場合は1m下を見る。
			endPos.y -= 1.0f;
		}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SSweepResultGround callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos.Set(start.getOrigin());
		//衝突検出。
		if (fabsf(addPosY.y) > FLT_EPSILON && (start.getOrigin().y() - end.getOrigin().y() != 0.0f))
		{
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		}
		if (callback.isHit)
		{
			//当たった。
			m_moveSpeed.y = 0.0f;
			m_isJump = false;
			m_isOnGround = true;
			nextPosition.y = callback.hitPos.y;
		}
		else
		{
			//地面上にいない
			m_isOnGround = false;
		}
		if (callback.hitObject != nullptr && m_rigidBody.GetBody()->getUserIndex() == enCollisionAttr_Character)
		{
			//const_cast<btCollisionObject*>(callback.hitObject)->setPlayerCollisionGroundFlg(true);
		}
		m_groundHitObject = callback.hitObject;

	}
	//上方向を調べる
	{
		m_position = nextPosition;	//移動の仮確定。
									//レイを作成する。
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//始点はカプセルコライダーの中心。
		start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		//終点は地面上にいない場合は1m下を見る。
		//地面上にいなくてジャンプで上昇中の場合は上昇量の0.01倍下を見る。
		//地面上にいなくて降下中の場合はそのまま落下先を調べる。
		CVector3 endPos;
		endPos.Set(start.getOrigin());
		if (!m_isOnGround)
		{
			if (addPosY.y > 0.0f)
			{
				//ジャンプ中とかで上昇中。
				//上昇中でもXZに移動した結果めり込んでいる可能性があるので下を調べる。
				endPos.y += addPosY.y;
			}
			else
			{
				endPos.y -= addPosY.y * 0.01f;
			}
		}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SSweepResultCeiling callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos.Set(start.getOrigin());
		//衝突検出。
		if (fabsf(addPosY.y) > FLT_EPSILON && (start.getOrigin().y() - end.getOrigin().y() != 0.0f))
		{
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		}
		if (callback.isHit)
		{
			//当たった。
			m_moveSpeed.y = 0.0f;
			nextPosition.y = callback.hitPos.y - (m_height + m_radius * 2.0f + 0.1f);
		}
	}
	//移動確定。
	m_position = nextPosition;
	m_position.y += m_rigidBodyManip;
	const btRigidBody* btBody = m_rigidBody.GetBody();
	//剛体を動かす。
	btBody->setActivationState(DISABLE_DEACTIVATION);
	//剛体の一を更新
	m_rigidBody.SetPosition(m_position);
	m_position.y -= m_rigidBodyManip;
	//@todo 未対応。 trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
}

void CCharacterController::StaticExecute()
{
	const int rayNum = 4;
	const float rayLength = 1.0f;
	//4方向のXZ平面にレイを飛ばす
	CVector3 ray[rayNum] =
	{
		{ rayLength,	0.0f, 0.0f},
		{ -rayLength,	0.0f, 0.0f },
		{ 0.0f,			0.0f, rayLength },
		{ 0.0f,			0.0f, -rayLength },
	};

	for (int i = 0; i < rayNum; i++)
	{
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//レイの終点を現在を座標とし外側から現在の座標に向かってレイを飛ばす
		CVector3 endPos = m_position;
		end.setOrigin(btVector3(endPos.x, endPos.y + m_height * 0.5f + m_radius , endPos.z));
		CVector3 startPos = m_position;
		startPos += ray[i];
		//高さが違うのでyの値だけ終点と同じものを使う
		start.setOrigin(btVector3(startPos.x, end.getOrigin().y(), startPos.z));
		SSweepResultWall callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos = startPos;
		callback.ray.Set(end.getOrigin() - start.getOrigin());
		PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		//もしレイが当たっていて、さらに押し戻す方向とオブジェクトの移動方向が一致している場合(引っ付き防止)
		if(callback.isHit && callback.isRay /*&& fabs(rayLength - callback.dist) < m_radius + 0.1f*/)
		{
		
			CVector3 hitNormal = callback.hitNormal;
			hitNormal.y = 0.0f;
			hitNormal.Normalize();
			m_wallNormal = hitNormal;
			CVector3 sinking;
			CVector3 endVector;
			endVector.Set(end.getOrigin());
			sinking = callback.hitPos - endVector;
			sinking.y = 0.0f;
			float projection = hitNormal.Dot(sinking);
			hitNormal *= (projection + m_radius);
			m_position += hitNormal;
		}
	}
}

void CCharacterController::RemovedRigidBody()
{
	m_rigidBody.Release();
}

void CCharacterController::Draw()
{
	btTransform transform = m_rigidBody.GetBody()->getWorldTransform();

	btVector3& position = transform.getOrigin();
	position.setY(position.y() + m_radius + m_height * 0.5f - m_rigidBodyManip);
	PhysicsWorld().DebugDraw(transform, m_collider.GetBody());
}