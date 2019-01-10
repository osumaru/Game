/*
*	ボスクラス
*/
#pragma once

class CBossHp;
class CWeekPoint;
struct SmawStatus {
	int Strength;			//攻撃力
	int Defense;			//防御力
	int	Hp;					//体力
	int MaxHp;				//最大体力
	int Gold;				//所持金額
};

class CMaw :
	public IGameObject
{
public:

	enum EnMawState {
		enState_Idle,			//待機
		enState_Walk,			//歩き
		enState_Attack,			//攻撃
		enState_SpecialAttack,	//特殊攻撃
		enState_Damage,			//ダメージ
		enState_Down,			//ダウン
		enState_Death,			//死亡
		enState_Num,			//状態の数
		enState_Invald,			//何もない
	};
	//コンストラクタ
	CMaw();
	//デストラクタ
	~CMaw();

	//プレイヤーの初期化
	void Init(const CVector3 position);

	//プレイヤーの更新関数
	void Update()override;

	//プレイヤーの描画関数
	void Draw()override;

	//死亡する前に呼ばれる関数
	void BeforeDead() override;

	//行動の選択
	//void ActionStateOrder();

	//回転
	void Rotation();

	//弱点スプライト描画
	void WeekPointUpdate();

	//通常攻撃
	void Attack();

	//特殊攻撃
	void SpecialAttack();

	//ダウン状態
	void Down();

	//プレイヤーを探す回転なども
	void Search();

	//待機状態
	void Idle();

	//死亡
	void Death();

	//アニメーション
	bool Anim(EnMawState animState);

	//インスタンスの取得
	static CMaw& GetInstance()
	{
		return *m_maw;
	}

	//インスタンスの生成
	static void CMaw::Create()
	{
		if (!m_maw)
		{
			m_maw = New<CMaw>(PRIORITY_ENEMY);
		}
	}

	//インスタンスの消去
	static void CMaw::Destroy()
	{
		Delete(m_maw);
		m_maw = nullptr;
	}

	//座標を取得
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//弱点座標を取得
	const CVector3& GetWeekPosition() const
	{
		return m_weekPosition;
	}

	//ダメージ判定を取得
	bool GetIsDamage()
	{
		return m_isDamage;
	}

	//攻撃判定を取得
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	//発見判定を取得
	bool GetIsBattle()
	{
		return m_isBattle;
	}

	//ダウン状態を取得
	bool GetIsDown()
	{
		return m_isDown;
	}

	//ボーンのワールド行列を取得
	const CMatrix& GetBoneMatrix(const wchar_t* boneName) const
	{
		return m_skinModel.FindBoneWorldMatrix(boneName);
	}
	//ステータスの取得
	const SmawStatus& GetSmawStatus() const
	{
		return m_status;
	}

	//ダメージ判定を設定
	//isDamage	ダメージフラグ
	void SetIsDamage(bool isDamage);

	//手を使った攻撃
	void HandAttack(float DamageLength);

	//アニメーションイベントが起きた時に呼ばれる処理。
	//animClipName アニメーションのファイルパス
	//enentName		アニメーションイベント名
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);

	//ワールド行列の取得
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinModel.GetWorldMatrix();
	}

private:
	//行動パターン
	enum EnMawActionPattern
	{
		enActionPatternAttack,			//攻撃
		enActionPatternSpecialAttack,	//特殊攻撃
		enActionPatternIdle,			//待機
		enActionPatternSearch,			//探す
		enActionPatternDown,			//ダウン
		enActionPatternDeath,			//死亡
		enActionPatternNum,				//数
	};

	static CMaw*			m_maw;										//ボス
	CVector3				m_position;									//座標
	CQuaternion				m_rotation = CQuaternion::Identity;			//回転
	CVector3				m_scale = { 3.0f,3.0f, 3.0f };				//拡大
	CSkinModel				m_skinModel;								//スキンモデル
	CCharacterController	m_characterController;						//キャラクターコントローラー
	CAnimation				m_animation;								//アニメーション
	SmawStatus				m_status;									//ステータス
	EnMawActionPattern		m_actionPattern;							//行動パターン
	CVector3				m_weekPosition;								//弱点座標

	int						m_downCount = 0;							//何回攻撃を受けたか
	float					m_downTime=0.0f;							//ダウンしている時間
	float					m_damageInterval = 0.0f;					//ダメージ間隔

	bool					m_isAttack = false;							//攻撃判定
	bool					m_isStand = false;							//待機判定
	bool					m_isDamage = false;							//ダメージ判定
	bool					m_isDown = false;							//ダウン判定
	bool					m_isDeath = false;							//死亡判定
	bool					m_isBattle = false;							//発見判定

	CBossHp*		m_bossHp = nullptr;			//ボスHP
	CWeekPoint*		m_weekPoint = nullptr;		//ボスの弱点スプライト
};

//ボスの取得
static CMaw& GetMaw()
{
	return CMaw::GetInstance();
}

