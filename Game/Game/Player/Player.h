#pragma once
#include "PlayerSate/PlayerStateMachine.h"

struct SplayerStatus
{
	int Strength;			//攻撃力
	int Defense;			//防御力
	int	Health;				//体力
	int MaxHealth;
	int Level;				//レベル
	int ExperiencePoint	;	//現在の経験値
	int NextExp;			//レベルアップまでに必要な経験値
	int OldExp;				//現在のレベルアップに必要だった経験値
	int AccumulationExp;	//累積経験値
	int Gold;

};

class CPlayer : public IGameObject
{

public:
	enum EnPlayerAnimeState
	{
		enPlayerStand,		//待機アニメーション
		enPlayerWalk,		//歩行アニメーション
		enPlayerRun,		//走りアニメーション
		enPlayerJump,		//ジャンプアニメーション
		enPlayerAttack,		//攻撃アニメーション
		enPlayerDamage,		//ダメージアニメーション
		enPlayerAvoidance,	//回避アニメーション
		enPlayerDete,		//死亡アニメーション
		enPlayerArroAttack,	//弓のアニメーション
		enPlayerNum			//アニメーションの数

	};

	//プレイヤーの初期化
	void Init(CVector3 position);

	//プレイヤーのインスタンスの取得
	static CPlayer& GetInstance()
	{
		static CPlayer player;
		return player;
	}

	//プレイヤーの更新関数
	void Update()override;

	//プレイヤーの描画関数
	void Draw()override;

	//プレイヤーの座標を取得する関数
	const CVector3 GetPosition()
	{
		return m_position;
	}

	//プレイヤーの移動処理を行う関数
	void Move();

	//プレイヤーの回転を行う関数
	void Rotation();

	//プレイヤーのアニメーションの処理を行う関数
	void AnimationMove();

	//ステータスの計算処理を行う関数
	void StatusCalculation();

	//プレイヤーの経験値量を上げる関数（セットする関数ではないです）
	//引数で倒した敵の経験値量を入れる
	void ExpUP(const int expup)
	{
		m_status.ExperiencePoint += expup;
		m_status.AccumulationExp += expup;
	}

	//アニメーションの設定
	void SetPlayerAnimation(const int animNumber, const float num)
	{
		m_animation.Play(animNumber, num);
		m_State = (EnPlayerAnimeState)animNumber;
	}

	//アニメーションの取得
	const CAnimation& GetAnimetion()
	{
		return m_animation;
	}

	//プレイヤーのステータスを取得
	const SplayerStatus& GetStatus()
	{
		return m_status;
	}

	//プレイヤーのワールド行列を取得
	const CMatrix& GetWorldMatrix()
	{
		return m_skinmodel.GetWorldMatrix();
	}

	//プレイヤーのスピードを取得する
	const CVector3& GetMoveSpeed()
	{
		return m_moveSpeed;
	}

	//プレイヤーの装備の変更を行う処理
	void WeaponChange();

	//プレイヤーの頭のボーンの位置を取得
	const CVector3 GetPlayerHead()
	{
		
		CMatrix PlayerHead = m_skinmodel.FindBoneWorldMatrix(L"Head");
		CVector3 PlayerHeadPos = { PlayerHead.m[3][0],PlayerHead.m[3][1],PlayerHead.m[3][2] };

		return PlayerHeadPos;
	}

	void PlayerAttack();
	//デバック用関数
	void GetDamage()
	{
		if (!m_isDamege)
		{

			m_status.Health -= 5;
			m_isDamege = true;
		}
	}
	//プレイヤーが生きているかの判定
	bool GetIsDied()
	{
		return m_isDied;
	}
	
	CPlayerStateMachine& SetPlayerStateMachine()
	{
		return m_PlayerStateMachine;
	}

private:
	

	CVector3				m_position;										//座標
	CVector3				m_WeaponPosition;								//武器の座標
	CVector3				m_moveSpeed = CVector3::Zero;					//移動速度
	CQuaternion				m_rotation = CQuaternion::Identity;				//回転
	CQuaternion				m_WeaponRotation = CQuaternion::Identity;		//武器の回転
	CSkinModel				m_skinmodel;									//スキンモデル
	CSkinModel				m_Weaponskin;									//武器のスキンモデル
	CCharacterController	m_characterController;							//キャラクターコントローラー
	
	CBoxCollider			m_weponBoxCollider;
	CRigidBody				m_weponRigitBody;

	CPad					m_pad;									//パッド
	CAnimation				m_animation;							//アニメーション
	SplayerStatus			m_status;								//プレイヤーのステータス
	bool					m_isSlip = false;						//スリップ判定
	float					m_slipSpeed = 2.0f;						//回避移動時のスピード
	EnPlayerAnimeState		m_State = enPlayerStand;				//アニメーションを遷移させるための変数
	const float				RUN_SPEED	= 2.8f;				
	const float				WALK_SPEED	= 200.0f;
	bool					m_isDamege = false;
	float					m_animetionFrame = 0.0f;
	bool					m_isAttack = false;
	bool					m_isDied = false;
	CPlayerStateMachine		m_PlayerStateMachine;
	

};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}