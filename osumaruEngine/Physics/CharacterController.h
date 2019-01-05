#pragma once

#include "Collider\CapsuleCollider.h"
#include "RigidBody.h"


const float cPI = 3.14159265358979323846f;

//キャラクターコントローラー
//衝突解決と衝突判定をしてくれるクラス。

class CCharacterController
{
public:
	//コンストラクタ
	CCharacterController();

	//デストラクタ
	~CCharacterController();

	/*
	初期化関数
	float		radius		キャラクターの半径　　　
	float		height		キャラクターの高さ　
	Vector3 position	キャラの座標

	コライダーはカプセルコライダーでキャラクターの原点が足元にあることを前提としている。
	*/
	void Init(float radius, float height, const CVector3& position);

	//実行関数
	void Execute(float deltaTime);

	//動いてるオブジェクトとのあたり判定をとる
	void DynamicExecute();

	//座標を取得。
	const CVector3 GetPosition() const
	{
		CVector3 rigidPos = m_rigidBody.GetPosition();
		rigidPos.y -= m_radius + m_height * 0.5f;
		return rigidPos;
	}

	//座標を設定。
	void SetPosition(const CVector3& pos)
	{
		CVector3 rigidPos = pos;
		rigidPos.y += m_radius + m_height * 0.5f;
		m_rigidBody.SetPosition(rigidPos);
	}

	//移動速度を設定。
	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_moveSpeed = moveSpeed;
		//上向きに移動速度が与えられていた場合ジャンプするとみなす
		if (m_moveSpeed.y > 0.0f)
		{
			Jump();
		}
	}
	
	//移動速度を取得。
	const CVector3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}

	//ジャンプするときに呼ばれる関数。
	void Jump()
	{
		m_isJump = true;
		m_isOnGround = false;
	}

	//ジャンプしているか？
	bool IsJump() const
	{
		return m_isJump;
	}

	//地面に接地しているか？
	bool IsOnGround() const
	{
		return m_isOnGround;
	}

	//コライダーを取得。
	const CCapsuleCollider* GetCollider() const
	{
		return &m_collider;
	}

	//重力を設定。
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}

	//重力を取得
	float GetGravity() const
	{
		return m_gravity;
	}

	//当たってほしくない剛体を登録
	void SetIgnoreRigidBody(const CRigidBody* rigidBody)
	{
		m_ignoreRigidBody = rigidBody;
	}

	//剛体を取得
	const CRigidBody& GetBody() const 
	{
		return m_rigidBody;
	}

	//剛体を削除。
	void RemovedRigidBody();

	//当たっている地面のオブジェクトを取得
	const btCollisionObject* GetGroundCollisionObject() const
	{
		return m_groundHitObject;
	}

	//当たっている壁のオブジェクトを取得
	const btCollisionObject* GetWallCollisionObject() const
	{
		return m_wallHitObject;
	}

	//壁の法線を取得
	const CVector3& GetWallNormal() const
	{
		return m_wallNormal;
	}

	//ユーザーインデックスを設定
	void SetUserIndex(int userNum)
	{
		m_rigidBody.SetUserIndex(userNum);
	}

	//剛体を描画
	void Draw();

	//何かに当たったかのフラグを返す
	bool IsHit() const
	{
		return m_wallHitObject != nullptr || m_groundHitObject != nullptr;
	}
private:
	CVector3					m_moveSpeed;			//移動速度
	bool						m_isJump;				//ジャンプしているか？
	bool						m_isOnGround;			//地面に設置しているか？
	CCapsuleCollider			m_collider;				//コライダー
	float						m_radius;				//半径
	float						m_height;				//高さ
	CRigidBody					m_rigidBody;			//剛体
	const CRigidBody*			m_ignoreRigidBody;		//当たってほしくない剛体のインスタンス
	float						m_gravity;				//重力
	const btCollisionObject*	m_groundHitObject;		//当たっている地面のオブジェクト
	const btCollisionObject*	m_wallHitObject;		//当たっている壁のオブジェクト
	CVector3					m_wallNormal;			//当たった壁の法線
};