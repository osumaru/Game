/*
*	敵のインターフェースクラス
*/

#pragma once

#include "EnemyState/EnemyStateMachine.h"
#include "EnemyTurn.h"
#include "EnemySearch.h"
#include "RespawnData.h"
#include "../Map/MapChip/MapChip.h"

class CEnemyGroup;

class IEnemy : public MapChip
{
public:
	struct SEnemyStatus
	{
		int level;		//レベル
		int strength;	//攻撃力
		int defense;	//防御力
		int	hp;			//体力
		int maxHp;		//最大体力
		int gold;		//所持金額
		int exp;		//経験値
	};

	//コンストラクタ
	IEnemy();

	//デストラクタ
	virtual ~IEnemy();

	void Init(const SMapChipInfo& info, CAnimation* anim = nullptr)override;

	//初期化
	//level		レベル
	virtual void Init(int level) {};

	virtual bool Start()override;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() {};

	//アニメーションイベント用の関数
	virtual void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName) {};

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

	//敵の攻撃(敵の種類によって変わる)
	virtual void Attack() {};

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

	//キャラクターコントローラーを取得
	const CCharacterController& GetCharacterController() const
	{
		return m_characterController;
	}

	//キャラクターコントローラーを取得
	CCharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	//ライトを取得
	CLight& GetLight()
	{
		return m_light;
	}

	//アニメーションを取得
	CAnimation& GetAnimation()
	{
		return m_animation;
	}

	//スキンモデルを取得
	CSkinModel& GetSkinModel()
	{
		return m_skinModel;
	}

	//ワールド行列を取得
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}

	//当たり判定用の腰のワールド行列を取得
	const CMatrix* GetWorldMatrixSpine() const
	{
		return m_spineMatrix;
	}

	//エネミーのボーンのワールド行列を取得
	//boneName	ボーンの名前
	const CMatrix& GetBoneWorldMatrix(const wchar_t* boneName) const
	{
		return m_skinModel.FindBoneWorldMatrix(boneName);
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
	void SetEnemyGroup(CEnemyGroup* enemyGroup);

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
	bool GetIsDamage() const
	{
		return m_isDamage;
	}

	//ダメージを受けたらフラグを設定する
	void SetIsDamage(bool isDamage)
	{
		m_isDamage = isDamage;
	}

	//ダメージを受けられるか
	bool* IsDamagePossible()
	{
		return m_isDamagePossible.get();
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

	//ステートマシンを取得
	const CEnemyStateMachine& GetStateMachine() const
	{
		return m_enemyStateMachine;
	}

	//死亡したかを取得
	bool GetIsDead()
	{
		return m_isDead;
	}

	//死亡したかを設定
	void SetIsDead(bool isDead)
	{
		m_isDead = isDead;
	}

	//エネミーの種類を取得
	EnEnemyType GetEnemyType()
	{
		return m_type;
	}

	//攻撃しているかを取得
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	//攻撃しているかを設定
	//isAttack	攻撃しているか
	void SetIsAttack(bool isAttack)
	{
		m_isAttack = isAttack;
	}

protected:
	CAnimation						m_animation;					//アニメーション
	CEnemyStateMachine				m_enemyStateMachine;			//ステートマシン
	CEnemyTurn						m_enemyTurn;					//向きを回転
	CEnemySearch					m_enemySearch;					//プレイヤーを探索
	CEnemyGroup*					m_enemyGroup = nullptr;					//エネミーグループ
	CCharacterController			m_characterController;			//キャラクターコントローラー
	CLight							m_light;						//ライト
	CEffect							m_auraEffect;					//オーラエフェクト
	SEnemyStatus					m_status;						//ステータス
	EnEnemyType						m_type;							//エネミーの種類
	EnAttackType					m_attackType = enAttackType_Near; //攻撃タイプ
	std::list<IEnemy*>::iterator	m_iterater;						//自身のイテレータ
	const CMatrix*					m_spineMatrix;					//当たり判定用の腰のワールド行列
	const int						m_maxPlayerHit = 2;				//最大攻撃ヒット数
	int								m_effectInterval = 0;			//エフェクトを発生させるインターバル
	float							m_attackLength = 1.2f;			//攻撃できる距離
	bool							m_isFind = false;				//プレイヤーを発見したか
	bool							m_isDamage = false;				//ダメージを受けたか
	std::unique_ptr<bool[]>			m_isDamagePossible;				//ダメージを受けられるか
	bool							m_isWireHit = false;			//ワイヤーが当たったか
	bool							m_isAttack = false;				//攻撃しているか
	bool							m_isDead = false;				//死亡したか
};