#include "engineStdafx.h"
#include "CharacterController.h"
#include "Physics.h"
#include "CollisionAttr.h"
#include "../Engine.h"


//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
struct SSweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//�Փ˃t���O�B
	CVector3 hitPos = { 0.0f, 0.0f, 0.0f };		//�Փ˓_�B
	CVector3 startPos = { 0.0f, 0.0f, 0.0f };	//���C�̎n�_�B
	CVector3 hitNormal = { 0.0f, 0.0f, 0.0f };	//�Փ˓_�̖@��
	const btCollisionObject* hitObject = nullptr;
	const btCollisionObject* me = nullptr;				//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
	float dist = FLT_MAX;							//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
													//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Detection ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Item)
		{
			//�����ɏՓ˂����Bor�L�����N�^�����̃R���W�����ƏՓ˂����B
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//�Փ˓_�̖@�������������Ă���
		CVector3	hitNormalTmp;
		hitNormalTmp.Set(convexResult.m_hitNormalLocal);
		//������Ɩ@���̂Ȃ��p�x�����߂�B
		CVector3 up = { 0.0f, 1.0f, 0.0f };
		float angle = hitNormalTmp.Dot(up);
		
		angle = fabsf(acosf(angle));
		if (angle < cPI * 0.45f ||		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B�p�x�����W�A���P�ʂȂ̂�180�x��cPI
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground)//�������̓R���W�����������n�ʂƎw�肳��Ă���B
		{

			//�Փ˂��Ă���B
			isHit = true;
			CVector3 hitPosTmp;
			hitPosTmp.Set(convexResult.m_hitPointLocal);
			//�Փ˓_�̋��������߂�B
			CVector3 vDist;
			vDist = hitPosTmp - startPos;
			float distTmp = vDist.Length();
			if (dist > distTmp)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				hitPos = hitPosTmp;
				hitNormal.Set(convexResult.m_hitNormalLocal);
				dist = distTmp;
			}
		}
		return 0.0f;
	}
};

//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�V��p)
struct SSweepResultCeiling : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//�Փ˃t���O�B
	CVector3 hitPos = { 0.0f, 0.0f, 0.0f };		//�Փ˓_�B
	CVector3 startPos = { 0.0f, 0.0f, 0.0f };	//���C�̎n�_�B
	CVector3 hitNormal = { 0.0f, 0.0f, 0.0f };	//�Փ˓_�̖@��
	const btCollisionObject* hitObject = nullptr;
	const btCollisionObject* me = nullptr;				//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
	float dist = FLT_MAX;							//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
													//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Detection ||
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Item)
		{
			//�����ɏՓ˂����Bor�L�����N�^�����̃R���W�����ƏՓ˂����B
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//�Փ˓_�̖@�������������Ă���
		CVector3	hitNormalTmp;
		hitNormalTmp.Set(convexResult.m_hitNormalLocal);
		//�������Ɩ@���̂Ȃ��p�x�����߂�B
		CVector3 up = { 0.0f, -1.0f, 0.0f };
		float angle = hitNormalTmp.Dot(up);
		angle = fabsf(acosf(angle));
		if (angle < cPI * 0.3f ||		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B�p�x�����W�A���P�ʂȂ̂�180�x��cPI
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground)//�������̓R���W�����������n�ʂƎw�肳��Ă���B
		{
			//�Փ˂��Ă���B
			isHit = true;
			CVector3 hitPosTmp;
			hitPosTmp.Set(convexResult.m_hitPointLocal);
			//�Փ˓_�̋��������߂�B
			CVector3 vDist;
			vDist = hitPosTmp - startPos;
			float distTmp = vDist.Length();
			if (dist > distTmp)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
				hitPos = hitPosTmp;
				hitNormal.Set(convexResult.m_hitNormalLocal);
				dist = distTmp;
			}
		}
		return 0.0f;
	}
};

//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
struct SSweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;								//�Փ˃t���O�B
	CVector3 hitPos = { 0.0f, 0.0f, 0.0f };		//�Փ˓_�B
	CVector3 startPos = { 0.0f, 0.0f, 0.0f };	//���C�̎n�_�B
	CVector3 ray = { 0.0f, 0.0f, 0.0f };
	bool		isRay = false;
	float		distance = 0.0f;
	float dist = FLT_MAX;							//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
	CVector3	hitNormal = { 0.0f, 0.0f, 0.0f };	//�Փ˓_�̖@��
	const btCollisionObject* me = NULL;					//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
	const btCollisionObject* hitObject = NULL;
													//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐�
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == me)
		{
			//�����ɏՓ˂����Bor�n�ʂɏՓ˂����B
			return 0.0f;
		}
		hitObject = convexResult.m_hitCollisionObject;
		//�Փ˓_�̖@�������������Ă���B
		CVector3 hitNormalTmp;
		hitNormalTmp.Set(convexResult.m_hitNormalLocal);
		//������ƏՓ˓_�̖@���̂Ȃ��p�x�����߂�
		CVector3 up = { 0.0f, 1.0f, 0.0f };
		float angle = hitNormalTmp.Dot(up);
		angle = fabsf(acosf(angle));
		if (angle >= cPI * 0.3f ||		//�n�ʂ̌X�΂�54�x�ȏ�Ȃ̂ŕǂƂ݂Ȃ��B
			convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character)//�������̓R���W�����������L�����N�^�Ȃ̂ŕǂƂ݂Ȃ��B
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
			//��_�Ƃ̋����𒲂ׂ�B
			CVector3 vDist;
			vDist = hitPosTmp - startPos;
			vDist.y = 0.0f;
			float distTmp = vDist.Length();
			if (distTmp < dist)
			{
				//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
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
	m_wallNormal(0.0f, 0.0f, 0.0f)
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
	//�R���W�����쐬�B
	m_radius = radius;
	m_height = height;
	m_collider.Create(m_radius, m_height);

	//���̂��������B
	SRigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	//���̂̈ʒu���X�V�B
	CVector3 rigidPos = m_position;
	rigidPos.y += m_radius + m_height * 0.5f;
	m_rigidBody.SetPosition(rigidPos);
	//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.SetUserIndex(enCollisionAttr_Character);
	//m_rigidBody.SetCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
}

void CCharacterController::Execute(float deltaTime)
{
	//StaticExecute();
	CPhysicsWorld& physicsWorld = PhysicsWorld();
	//���x�ɏd�͉����x��������B
	m_moveSpeed.y += m_gravity * deltaTime;
	//���̈ړ���ƂȂ���W���v�Z����B
	CVector3 nextPosition = m_position;
	//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
	CVector3 addPos = m_moveSpeed;
	addPos *= deltaTime;
	nextPosition += addPos;
	CVector3 originalXZDir = addPos;
	originalXZDir.y = 0.0f;
	originalXZDir.Normalize();

	//XZ���ʂł̏Փˌ��o�ƏՓˉ������s���B
	{
		int loopCount = 0;
		const btCollisionObject* wallCollisionObject = nullptr;
		CVector3 hitNormal = { 0.0f, 0.0f, 0.0f };
		while (true)
		{
			//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
			CVector3  addPosXZ;
			addPosXZ = nextPosition - m_position;
			addPosXZ.y = 0.0f;
			if (addPosXZ.Length() < FLT_EPSILON)
			{
				//XZ���ʂœ������Ȃ��̂Œ��ׂ�K�v�Ȃ��B
				//FLTEPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
				//�ƂĂ��������l�̂��Ƃł��B
				break;
			}
			//�J�v�Z���R���C�_�[�̒��S���W�@+ 0.2�̍��W��posTmp�ɋ��߂�B
			CVector3 posTmp = m_position;
			posTmp.y += m_height * 0.5f + m_radius + 0.2f;
			//���C���쐬�B
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmpd�ɋ��߂�B
			start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
			//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
			end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

			SSweepResultWall callback;
			callback.me = m_rigidBody.GetBody();
			callback.startPos = posTmp;
			//�Փˌ��o�B
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
			if (callback.isHit)
			{
				wallCollisionObject = callback.hitObject;
				//���������B
				//�ǁB
				CVector3 vT0, vT1;
				//XZ���ʂł̈ړ���̍��W��vT0�ɁA��_(�Փ˓_)��vT1�ɐݒ肷��B
				vT0 = { nextPosition.x, 0.0f, nextPosition.z };
				vT1 = { callback.hitPos.x, 0.0f, callback.hitPos.z };
				//�߂荞�݂��������Ă���ړ��x�N�g�������߂�B
				CVector3 vMerikomi;
				vMerikomi = vT1 - vT0;

				//XZ���ʂł̏Փ˂����ǂ̖@�������߂�B
				CVector3 hitNormalXZ = callback.hitNormal;
				hitNormalXZ.y = 0.0f;
				hitNormalXZ.Normalize();
				hitNormal = hitNormalXZ;
				//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����B
				float fT0 = hitNormalXZ.Dot(vMerikomi);
				//�����߂��Ԃ��x�N�g�������߂�B
				//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g���B
				CVector3 vOffset;
				vOffset = hitNormalXZ;
				vOffset *= (fT0 + m_radius);//�R���C�_�[�̔��a���蓮�Ŗ߂��Ă���
				nextPosition += vOffset;
				CVector3 currentDir;
				currentDir = nextPosition - m_position;
				currentDir.y = 0.0f;
				currentDir.Normalize();
				if (currentDir.Dot(originalXZDir) < 0.0f)
				{
					//�p�ɓ��������̃L�����N�^�̐U����h�~���邽�߂ɁA
					//�ړ��悪�t����
					nextPosition.x = m_position.x;
					nextPosition.z = m_position.z;
					break;
				}
			}
			else
			{
				//�ǂ��Ƃ�������Ȃ��̂ŏI���B
				break;
			}
			m_wallHitObject = callback.hitObject;
			loopCount++;
			if (loopCount == 5)
			{
				break;
			}
			if (callback.hitObject != nullptr && m_rigidBody.GetBody()->getUserIndex() == enCollisionAttr_Player)
			{
				const_cast<btCollisionObject*>(callback.hitObject)->setPlayerCollisionWallFlg(true);
			}
		}
		m_wallNormal = hitNormal;
		m_wallHitObject = wallCollisionObject;
	}
	//XZ�̈ړ��͊m��B
	m_position.x = nextPosition.x;
	m_position.z = nextPosition.z;

	CVector3 addPosY;
	addPosY = nextPosition - m_position;
	//�������𒲂ׂ�B
	{
		m_position = nextPosition;	//�ړ��̉��m��B
									//���C���쐬����B
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
		start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
		//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
		//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
		CVector3 endPos;
		endPos.Set(start.getOrigin());
		if (!m_isOnGround)
		{
			if (addPosY.y > 0.0f)
			{
				//�W�����v���Ƃ��ŏ㏸���B
				//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�B
				endPos.y -= addPosY.y * 0.01f;
			}
			else
			{
				endPos.y += addPosY.y;
			}
		}
		else
		{
			//�n�ʏ�ɂ���ꍇ��1m��������B
			endPos.y -= 1.0f;
		}
		end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));
		SSweepResultGround callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos.Set(start.getOrigin());
		//�Փˌ��o�B
		if (fabsf(addPosY.y) > FLT_EPSILON && (start.getOrigin().y() - end.getOrigin().y() != 0.0f))
		{
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		}
		if (callback.isHit)
		{
			//���������B
			m_moveSpeed.y = 0.0f;
			m_isJump = false;
			m_isOnGround = true;
			nextPosition.y = callback.hitPos.y;
		}
		else
		{
			//�n�ʏ�ɂ��Ȃ�
			m_isOnGround = false;
		}
		if (callback.hitObject != nullptr && m_rigidBody.GetBody()->getUserIndex() == enCollisionAttr_Player)
		{
			const_cast<btCollisionObject*>(callback.hitObject)->setPlayerCollisionGroundFlg(true);
		}
		m_groundHitObject = callback.hitObject;

	}
	//������𒲂ׂ�
	{
		m_position = nextPosition;	//�ړ��̉��m��B
									//���C���쐬����B
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
		start.setOrigin(btVector3(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z));
		//�I�_�͒n�ʏ�ɂ��Ȃ��ꍇ��1m��������B
		//�n�ʏ�ɂ��Ȃ��ăW�����v�ŏ㏸���̏ꍇ�͏㏸�ʂ�0.01�{��������B
		//�n�ʏ�ɂ��Ȃ��č~�����̏ꍇ�͂��̂܂ܗ�����𒲂ׂ�B
		CVector3 endPos;
		endPos.Set(start.getOrigin());
		if (!m_isOnGround)
		{
			if (addPosY.y > 0.0f)
			{
				//�W�����v���Ƃ��ŏ㏸���B
				//�㏸���ł�XZ�Ɉړ��������ʂ߂荞��ł���\��������̂ŉ��𒲂ׂ�B
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
		//�Փˌ��o�B
		if (fabsf(addPosY.y) > FLT_EPSILON && (start.getOrigin().y() - end.getOrigin().y() != 0.0f))
		{
			physicsWorld.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		}
		if (callback.isHit)
		{
			//���������B
			m_moveSpeed.y = 0.0f;
			nextPosition.y = callback.hitPos.y - (m_height + m_radius * 2.0f + 0.1f);
		}
	}
	//�ړ��m��B
	m_position = nextPosition;
	const btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	btBody->setActivationState(DISABLE_DEACTIVATION);
	//���̂̈���X�V
	CVector3 rigidPos = m_position;
	rigidPos.y += m_radius + m_height * 0.5f;
	m_rigidBody.SetPosition(rigidPos);
	//@todo ���Ή��B trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
}

void CCharacterController::StaticExecute()
{
	const int rayNum = 4;
	const float rayLength = 1.0f;
	//4������XZ���ʂɃ��C���΂�
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
		//���C�̏I�_�����݂����W�Ƃ��O�����猻�݂̍��W�Ɍ������ă��C���΂�
		CVector3 endPos = m_position;
		end.setOrigin(btVector3(endPos.x, endPos.y + m_height * 0.5f + m_radius , endPos.z));
		CVector3 startPos = m_position;
		startPos += ray[i];
		//�������Ⴄ�̂�y�̒l�����I�_�Ɠ������̂��g��
		start.setOrigin(btVector3(startPos.x, end.getOrigin().y(), startPos.z));
		SSweepResultWall callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos = startPos;
		callback.ray.Set(end.getOrigin() - start.getOrigin());
		PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);
		//�������C���������Ă��āA����ɉ����߂������ƃI�u�W�F�N�g�̈ړ���������v���Ă���ꍇ(�����t���h�~)
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
	PhysicsWorld().DebugDraw(transform, m_collider.GetBody());
}