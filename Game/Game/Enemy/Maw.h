/*
*	ボスクラス
*/
#pragma once

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

	//行動の選択
	void ActionStateOrder();

	//通常攻撃
	void Attack();

	//特殊攻撃
	void SpecialAttack();

	//ダウン状態
	void Down();

	//プレイヤーを探す回転なども
	void Find();

	//待機状態
	void Stand();

	//死亡
	void Death();

	//アニメーション
	bool Anim(EnMawState animState);

	//プレイヤーのインスタンスの取得
	static CMaw& GetInstance()
	{
		return *m_maw;
	}

	//インスタンスの生成
	static void CMaw::Create()
	{
		if (!m_maw)
		{
			m_maw = New<CMaw>(1);
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
	bool GetIsFind()
	{
		return m_isFind;
	}
	//手のワールド行列を取得
	const CVector3& GetLeftHandBone() const
	{
		CMatrix MawHand = m_skinModel.FindBoneWorldMatrix(L"RightHand");
		CVector3 LeftHandPos = { MawHand.m[3][0],MawHand.m[3][1] ,MawHand.m[3][2] };
		return LeftHandPos;
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

private:
	//行動パターン
	enum EnMawActionPattern
	{
		enActionPatternAttack,			//攻撃
		enActionPatternSpecialAttack,	//特殊攻撃
		enActionPatternStand,			//待機
		enActionPatternFind,			//探す
		enActionPatternDown,			//ダウン
		enActionPatternDeath,			//死亡
		enActionPatternNum,				//数
	};

	static CMaw*			m_maw;										//ボス
	CVector3				m_position;									//座標
	CQuaternion				m_rotation = CQuaternion::Identity;			//回転
	CVector3				m_scale = { 10.0f,10.0f, 10.0f };			//拡大
	CSkinModel				m_skinModel;								//スキンモデル
	CCharacterController	m_characterController;						//キャラクターコントローラー
	CAnimation				m_animation;								//アニメーション
	SmawStatus				m_status;									//ステータス
	EnMawActionPattern		m_actionPattern;							//行動パターン

	int						m_downCount = 0;							//何回攻撃を受けたか
	float					m_downTime=0.0f;							//ダウンしている時間
	float					m_damageInterval = 0.0f;					//ダメージ間隔

	bool					m_isAttack = false;							//攻撃判定
	bool					m_isStand = false;							//待機判定
	bool					m_isDamage = false;							//ダメージ判定
	bool					m_isDown = false;							//ダウン判定
	bool					m_isDeath = false;							//死亡判定
	bool					m_isFind = false;							//発見判定
};

//ボスの取得
static CMaw& GetMaw()
{
	return CMaw::GetInstance();
}

