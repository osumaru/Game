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
	void SetPosition(const CVector3& position)
	{
		m_rigidBody->getOneBeforeWorldTransform().setOrigin(m_rigidBody->getWorldTransform().getOrigin());
		m_rigidBody->getWorldTransform().setOrigin(btVector3(position.x, position.y, position.z));
	}

	//座標を取得
	CVector3 GetPosition() const
	{
		CVector3 position ;
		btVector3 btPos = m_rigidBody->getWorldTransform().getOrigin();
		position.x = btPos.x();
		position.y = btPos.y();
		position.z = btPos.z();
		return position;
	}


	//座標を取得
	CQuaternion GetRotation() const
	{
		CQuaternion rotation;
		btQuaternion btRot = m_rigidBody->getWorldTransform().getRotation();
		rotation.x = btRot.x();
		rotation.y = btRot.y();
		rotation.z = btRot.z();
		rotation.w = btRot.w();
		return rotation;
	}

	//回転を設定
	void SetRotation(const CQuaternion& rotation)
	{
		m_rigidBody->getOneBeforeWorldTransform().setRotation(m_rigidBody->getWorldTransform().getRotation());
		m_rigidBody->getWorldTransform().setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
	}

	//剛体を描画
	void Draw();

	//物理ワールドに剛体を登録
	void PhysicsWorldAddRigidBody();

	//物理ワールドに剛体をリストを外す
	void PhysicsWorldRemoveRigidBody();

	//ユーザーインデックスを設定
	void SetUserIndex(int index)
	{
		m_rigidBody->setUserIndex(index);
	}

	//コリジョンフラグを設定
	void SetCollisionFlags(int flag)
	{
		m_rigidBody->setCollisionFlags(flag);
	}

	//アクティベーションステートを設定
	void SetActivationState(int state)
	{
		m_rigidBody->setActivationState(state);
	}

	
	//void SetPlayerCollisionWallFlg(bool flg)
	//{
	//	m_rigidBody->setPlayerCollisionWallFlg(flg);
	//}

	//void SetPlayerCollisionGroundFlg(bool flg)
	//{
	//	m_rigidBody->setPlayerCollisionGroundFlg(flg);
	//}


private:
	std::unique_ptr<btDefaultMotionState>	m_myMotionState;		//モーションステイト
	std::unique_ptr<btRigidBody>			m_rigidBody;			//剛体
};
