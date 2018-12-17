/*
*	敵のインターフェースクラス
*/

#pragma once

#include "EnemyState/EnemyStateMachine.h"
#include "EnemyTurn.h"
#include "EnemySearch.h"
#include "../Player/Weapon/WeaponCommon.h"

class CEnemyGroup;

struct SEnemyStatus
{
	int strength;	//攻撃力
	int defense;	//防御力
	int	hp;			//体力
	int maxHp;		//最大体力
	int gold;		//所持金額
	int exp;		//経験値
};

class IEnemy : public IGameObject
{
public:
	//コンストラクタ
	IEnemy();

	//デストラクタ
	virtual ~IEnemy();

	//初期化
	//position	座標
	virtual void Init(CVector3 position) {};

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() {};

	void AddObject()
	{
		Add(&m_enemyStateMachine, 0);
		Add(&m_enemyTurn, 0);
		Add(&m_enemySearch, 0);
	}

	//死ぬ前に呼ばれる関数、解放処理などに使う
	void BeforeDead()override;

	//敵の向いている方向から扇上の範囲に入っているか判定する
	//degree	角度(デグリー)
	//position	扇上の範囲にいるか調べたい座標
	bool CalucFanShape(float degree, const CVector3& position);

	//自身をエネミーリストから削除
	void EnemyListErase();

	//当たり判定用の腰の座標を更新
	void UpdateSpinePos();

	//敵の攻撃(敵の種類によって変わる)
	virtual void Attack() {};

	//自身のイテレータを設定
	void SetIterater(std::list<IEnemy*>::iterator iterater)
	{
		m_iterater = iterater;
	}

	//敵の座標を取得
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//敵の座標を設定
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}

	//クォータニオンを取得
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	//クォータニオンを設定
	//rotation		クォータニオン
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}

	//移動速度を取得
	const CVector3& GetMoveSpeed() const
	{
		return m_characterController.GetMoveSpeed();
	}

	//移動速度を設定
	//moveSpeed		移動速度
	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

	//剛体を削除
	void RemovedRegidBody()
	{
		m_isRemovedRigidBody = true;
		m_characterController.RemovedRigidBody();
	}

	//アニメーションを取得
	CAnimation& GetAnimation()
	{
		return m_animation;
	}

	//ワールド行列を取得
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}

	//当たり判定用の腰のワールド行列を取得
	const CVector3& GetSpinePos() const
	{
		return m_spinePos;
	}

	//エネミーのボーンのワールド行列を取得
	//boneName	ボーンの名前
	const CMatrix& GetBoneWorldMatrix(const wchar_t* boneName) const
	{
		return m_skinModel.FindBoneWorldMatrix(boneName);
	}

	//ステートマシンをゲームオブジェクトから解放
	void StateMachineRelease()
	{
		m_enemyStateMachine.Release();
	}

	//ステータスを取得
	const SEnemyStatus& GetStatus() const
	{
		return m_status;
	}

	//HPを減らす
	//damage	ダメージ
	void HpDamage(int damage)
	{
		m_status.hp -= damage;
	}

	//所属するグループを設定
	//enemyGroup	エネミーの所属するグループのポインタ
	void SetEnemyGroup(CEnemyGroup* enemyGroup)
	{
		m_enemyGroup = enemyGroup;
	}

	//所属しているグループを取得
	CEnemyGroup* GetEnemyGroup()
	{
		return m_enemyGroup;
	}

	//プレイヤーを発見したか
	bool IsFind() const
	{
		return m_isFind;
	}

	//プレイヤーを発見したらフラグを設定する
	void SetIsFind(bool isFind)
	{
		m_isFind = isFind;
	}

	//ダメージを受けたか
	bool IsDamage() const
	{
		return m_isDamage;
	}

	//ダメージを受けたらフラグを設定する
	void SetIsDamage(bool isDamage)
	{
		m_isDamage = isDamage;
	}

	//ダメージを受けられるか
	bool IsDamagePossible() const
	{
		return m_isDamagePossible;
	}

	//ダメージを受けられるかのフラグを設定する
	void SetIsDamagePossible(bool isDamage)
	{
		m_isDamagePossible = isDamage;
	}

	//ワイヤーが当たったか
	bool IsWireHit() const
	{
		return m_isWireHit;
	}

	//ワイヤーが当たったらフラグを設定する
	void SetIsWireHit(bool isWireHit)
	{
		m_isWireHit = isWireHit;
	}

	//攻撃できる距離を取得
	float GetAttackLength()
	{
		return m_attackLength;
	}

	//攻撃できる距離を設定
	void SetAttackLength(float attackLength)
	{
		m_attackLength = attackLength;
	}

	//攻撃タイプ
	enum EnAttackType
	{
		enAttackType_Far,
		enAttackType_Near,
	};

	//攻撃タイプを取得
	EnAttackType GetAttackType()
	{
		return m_attackType;
	}

	//攻撃された武器を取得
	EnAttackWeapon GetAttackWeapon()
	{
		return m_attackWeapon;
	}

	//攻撃された武器を設定
	void SetAttackWeapon(EnAttackWeapon AttackWeapon)
	{
		m_attackWeapon=AttackWeapon;
	}

protected:
	CSkinModel						m_skinModel;					//スキンモデル
	CAnimation						m_animation;					//アニメーション
	CEnemyStateMachine				m_enemyStateMachine;			//ステートマシン
	CEnemyTurn						m_enemyTurn;					//向きを回転
	CEnemySearch					m_enemySearch;					//プレイヤーを探索
	CEnemyGroup*					m_enemyGroup;					//エネミーグループ
	CVector3						m_position;						//座標
	CQuaternion						m_rotation;						//回転
	CCharacterController			m_characterController;			//キャラクターコントローラー
	SEnemyStatus					m_status;						//ステータス
	EnAttackType					m_attackType = enAttackType_Near; //攻撃タイプ
	std::list<IEnemy*>::iterator	m_iterater;						//自身のイテレータ
	const CMatrix*					m_spineMatrix;					//当たり判定用の腰のワールド行列
	CVector3						m_spinePos;						//当たり判定用の腰の座標
	float							m_attackLength = 1.2f;			//攻撃できる距離
	bool							m_isFind = false;				//プレイヤーを発見したか
	bool							m_isDamage = false;				//ダメージを受けたか
	bool							m_isDamagePossible = true;		//ダメージを受けられるか
	bool							m_isWireHit = false;			//ワイヤーが当たったか
	bool							m_isRemovedRigidBody = false;	//剛体が削除されたか
	EnAttackWeapon					m_attackWeapon=enAttackWeaponNone;	//攻撃する武器
};