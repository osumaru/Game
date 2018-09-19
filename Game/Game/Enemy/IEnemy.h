/*
*	敵のインターフェースクラス
*/

#pragma once

#include "../Enemy/EnemyState/EnemyStateMachine.h"
#include "../UI/DamageNumber/DamageNumber.h"
#include "EnemyTurn.h"
#include "EnemySearch.h"
class CEnemyGroup;

class IEnemy : public IGameObject
{
public:
	//コンストラクタ
	IEnemy();

	//デストラクタ
	virtual ~IEnemy();

	//初期化
	//position	座標
	virtual void Init(CVector3 position) = 0;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;

	//敵の座標を取得
	const CVector3& GetPosition() const
	{
		return m_position;
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

	//エネミーのダメージ計算
	void DamageCalculation()
	{
		m_damageNumber.DamageCalculation();
	}

	//ダメージ表示のリセット
	void DamageIndicateReset()
	{
		m_damageNumber.Reset();
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

	//攻撃が当たったか
	bool IsAttackHit() const
	{
		return m_isAttackHit;
	}

	//攻撃が当たったらフラグを設定する
	void SetIsAttackHit(bool isAttackHit)
	{
		m_isAttackHit = isAttackHit;
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
	bool IsDamage()const
	{
		return m_isDamage;
	}

	//ダメージを受けたかのフラグを設定
	void SetIsDamage(bool isDamage)
	{
		m_isDamage = isDamage;
	}

protected:
	CSkinModel				m_skinModel;			//スキンモデル
	CCharacterController	m_characterController;	//キャラクターコントローラー
	CAnimation				m_animation;			//アニメーション
	CEnemyStateMachine		m_enemyStateMachine;	//ステートマシン
	CEnemyTurn				m_enemyTurn;			//向きを回転
	CEnemySearch			m_enemySearch;			//プレイヤーを探索
	CDamegeNumber			m_damageNumber;			//ダメージ数値
	CEnemyGroup*			m_enemyGroup;			//エネミーグループ
	CVector3				m_position;				//座標
	CQuaternion				m_rotation;				//回転
	int						m_animNum = 0;			//再生するアニメーション番号
	int						m_animNumOld = 0;		//1つ前のアニメーション番号
	bool					m_isAttackHit = false;	//攻撃が当たったか
	bool					m_isFind = false;		//プレイヤーを発見したか
	bool					m_isDamage = false;		//ダメージを受けたかの判定
};