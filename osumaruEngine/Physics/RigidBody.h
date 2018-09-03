#pragma once
class ICollider;

//剛体情報
struct SRigidBodyInfo
{
	SRigidBodyInfo()
	{
		collider = nullptr;
		mass = 0.0f;
		pos = { 0.0f, 0.0f, 0.0f };
		rot = { 0.0f, 0.0f, 0.0f, 1.0f };
	}
	CVector3 pos;			//座標
	CQuaternion rot;			//回転
	const ICollider* collider;		//コライダー
	float mass;					//質量、動かないものは0.0fでいい
};

//剛体のクラス
class CRigidBody : Uncopyable
{
public:
	//コンストラクタ
	CRigidBody() :
		m_myMotionState(nullptr),
		m_rigidBody(nullptr)
	{

	}

	//デストラクタ
	~CRigidBody()
	{
		Release();
	}

	/*
	初期化関数
	rbInfo.pos		座標(Vector3)
	rbInfo.rot		回転(Quaternion)
	rbInfo.collider	コライダー(ICollider*)
	mass			質量(float)
	*/
	void Create(const SRigidBodyInfo& rbInfo);

	//リリース関数
	void Release();

	//剛体を取得
	const btRigidBody* GetBody() const
	{
		return m_rigidBody.get();
	}

	//座標を設定
	void SetPosition(CVector3 position)
	{
		m_rigidBody->getOneBeforeWorldTransform().setOrigin(m_rigidBody->getWorldTransform().getOrigin());
		m_rigidBody->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	}

	//回転を設定
	void SetRotation(CQuaternion rotation)
	{
		m_rigidBody->getOneBeforeWorldTransform().setRotation(m_rigidBody->getWorldTransform().getRotation());
		m_rigidBody->getWorldTransform().setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
	}

	void Draw();

	void PhysicsWorldAddRigidBody();

	void PhysicsWorldRemoveRigidBody();


	void SetUserIndex(int index)
	{
		m_rigidBody->setUserIndex(index);
	}

	void SetCollisionFlags(int flag)
	{
		m_rigidBody->setCollisionFlags(flag);
	}

	void SetActivationState(int state)
	{
		m_rigidBody->setActivationState(state);
	}

	void SetPlayerCollisionWallFlg(bool flg)
	{
		m_rigidBody->setPlayerCollisionWallFlg(flg);
	}

	void SetPlayerCollisionGroundFlg(bool flg)
	{
		m_rigidBody->setPlayerCollisionGroundFlg(flg);
	}


private:
	std::unique_ptr<btDefaultMotionState>	m_myMotionState;		//モーションステイト
	std::unique_ptr<btRigidBody>			m_rigidBody;			//剛体
};
