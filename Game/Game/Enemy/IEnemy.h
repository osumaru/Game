/*
*	敵のインターフェースクラス
*/

#pragma once

#include "EnemyState/EnemyStateMachine.h"
#include "EnemyTurn.h"
#include "EnemySearch.h"

class CEnemyGroup;

struct SEnemyStatus
{
	int Strength;			//攻撃力
	int Defense;			//防御力
	int	Hp;					//体力
	int MaxHp;				//最大体力
	int Gold;				//所持金額
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

	//死ぬ前に呼ばれる関数、解放処理などに使う
	void BeforeDead()override;

	//敵の向いている方向から扇上の範囲に入っているか判定する
	//degree	角度(デグリー)
	//position	扇上の範囲にいるか調べたい座標
	bool CalucFanShape(float degree, const CVector3& position);

	//自身をエネミーリストから削除
	void EnemyListErase();

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

	//アニメーションを再生
	//animNum	アニメーション番号
	void PlayAnimation(int animNum)
	{
		m_animation.Play(animNum, 0.3f);
	}

	//アニメーションを再生しているか
	bool IsPlayAnimation() const
	{
		return m_animation.IsPlay();
	}

	//ワールド行列を取得
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
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
		m_status.Hp -= damage;
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

protected:
	CSkinModel					 m_skinModel;				//スキンモデル
	CAnimation					 m_animation;				//アニメーション
	CEnemyStateMachine			 m_enemyStateMachine;		//ステートマシン
	CEnemyTurn					 m_enemyTurn;				//向きを回転
	CEnemySearch				 m_enemySearch;				//プレイヤーを探索
	CEnemyGroup*				 m_enemyGroup;				//エネミーグループ
	CVector3					 m_position;				//座標
	CQuaternion					 m_rotation;				//回転
	CCharacterController		 m_characterController;		//キャラクターコントローラー
	SEnemyStatus			     m_status;					//ステータス
	std::list<IEnemy*>::iterator m_iterater;				//自身のイテレータ
	bool						 m_isAttackHit = false;		//攻撃が当たったか
	bool						 m_isFind = false;			//プレイヤーを発見したか
	bool						 m_isDamage = false;		//ダメージを受けたか
	bool						 m_isDamagePossible = true;	//ダメージを受けられるか
	bool						 m_isWireHit = false;		//ワイヤーが当たったか
};