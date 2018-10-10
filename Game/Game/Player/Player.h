#pragma once
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "PlayerRotation.h"
#include "PlayerMove.h"
#include "PlayerArrow.h"
#include "WireCollisionSolver.h"

struct SplayerStatus
{
	int Strength;			//攻撃力
	int Defense;			//防御力
	int	Health;				//体力
	int MaxHealth;			//レベルごとの最大HP
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
		enPlayerRunJump,	//走りジャンプ
		enPlayerJump,		//ジャンプアニメーション
		enPlayerAttack,		//攻撃アニメーション
		enPlayerAttack2,	//連撃アニメーション
		enPlayerDamage,		//ダメージアニメーション
		enPlayerAvoidance,	//回避アニメーション

		enPlayerDete,		//死亡アニメーション
		enPlayerArroAttack,	//弓のアニメーション
		enPlayerLongSwordAttack,//大剣の攻撃アニメーション
		enPlayerTwinSwordAttack,//二刀流の攻撃アニメーション
		enPlayerNum			//アニメーションの数

	};

	enum EnPlayerWeapon
	{
		enSword,			//片手剣
		enLongSword,		//両手剣
		enArro,				//弓矢
		enTwinSword,		//二刀

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
	//プレイヤーの座標を設定する関数
	void SetPosition(const CVector3 setpos)
	{
		 m_position = setpos;
	}
	//プレイヤーの回転情報を取得
	const CQuaternion& GetPlayerrRot()
	{
		return m_rotation;
	}
	//プレイヤーの回転の設定
	void SetPlayerRot(const CQuaternion Setrot)
	{
		m_rotation = Setrot;
	}
	//アニメーションの情報を取得
	const CAnimation& GetAnimation()
	{
		return m_animation;
	}
	CCharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	//ステータスの計算処理を行う関数
	void StatusCalculation();

	/*プレイヤーの経験値量を上げる関数（セットする関数ではないです）
	引数で倒した敵の経験値量を入れる*/
	void ExpUP(const int expup)
	{
		m_status.ExperiencePoint += expup;
		m_status.AccumulationExp += expup;
	}

	//プレイヤーのHP回復をする
	//recoveryValue		回復値
	void RecoveryHP(const int recoveryValue)
	{
		m_status.Health += recoveryValue;
		if (m_status.Health >= m_status.MaxHealth) {
			m_status.Health = m_status.MaxHealth;
		}
	}

	//プレイヤーがお金を取得する
	//gold		お金
	void GainGold(const int gold)
	{
		m_status.Gold += gold;
	}

	/*アニメーションの設定
	第一引数　アニメーメーションの番号　第二引数　補完時間*/
	void SetPlayerAnimation(const int animNumber, const float num)
	{
		m_animation.Play(animNumber, num);
		m_State = (EnPlayerAnimeState)animNumber;
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

	//プレイヤーのスピードの設定
	void SetMoveSpeed(const CVector3 setmovespeed)
	{
		m_moveSpeed = setmovespeed;
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
	//プレイヤーのダメージ処理
	void GetDamage()
	{
		if (!m_isDamege && !m_intervalOn)
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
	//死亡したかを設定
	void SetIsDeid(const bool SetDied)
	{
		m_isDied = SetDied;
	}
	//
	//ダメージを受けたかの判定
	bool GetIsDamage()
	{
		return m_isDamege;
	}
	//ダメージを受けたかの設定
	void SetIsDamage(const bool SetDamage)
	{
		m_isDamege = SetDamage;
	}
	//攻撃中かを取得
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	//攻撃をしたかの設定
	void SetAttack(const bool SetA)
	{
		m_isAttack = SetA;
	}
	//武器の剛体の取得
	CRigidBody& GetWeaponBody()
	{
		return m_weaponRigitBody;
	}
	//ステートマシーンのしゅとく
	CPlayerStateMachine& GetPlayerStateMachine()
	{
		return m_PlayerStateMachine;
	}
	//武器の切り替えを設定する関数
	void SetChangeWeapon(const int changeWeapon)
	{
		m_weaponState = (EnPlayerWeapon)changeWeapon;
		
	}
	//武器の座標の設定
	void SetWeaponPosition(const CVector3 swpos)
	{
		m_weaponPosition =  swpos;
	}
	//武器の座標を取得
	const CVector3 GetWeaponPosition()
	{
		return m_weaponPosition;
	}
	//武器の向きの設定
	void SetWeaponRotation(const CQuaternion setrot)
	{
		m_weaponRotation = setrot;
	}
	
	//プレイヤーのスキンモデルの情報を取得
	CSkinModel& GetPlayerSkin()
	{
		return m_skinmodel;
	}
	//プレイヤーが浮いているかを取得
	const bool GetIsGround()
	{	
		return m_isGround;
	}
	//無敵時間を設定する
	void SetInterval(const bool set)
	{
		m_intervalOn = set;
	}

	//ワイヤー移動する先の座標を取得
	const CVector3& GetWirePosition()
	{
		return m_wirePosition;
	}

	//ワイヤー移動できるかを取得
	bool IsWireMove()
	{
		return m_isWireMove;
	}

	const CSkinModel& GetWeaponskin(int num)
	{
		return m_weaponskin[num];
	}
	 
	const CVector3 GetTargetPos()
	{
		return m_cameraTargetPos;
	}

	void SetTargetPos(const CVector3 settar)
	{
		m_cameraTargetPos = settar;
	}

private:
	

	CVector3				m_position;										//座標
	CVector3				m_weaponPosition;								//武器の座標
	CVector3				m_moveSpeed = CVector3::Zero;					//移動速度
	CVector3				m_weaponScale = CVector3::One;
	CVector3				m_cameraTargetPos = CVector3::Zero;

	CQuaternion				m_rotation = CQuaternion::Identity;				//回転
	CQuaternion				m_weaponRotation = CQuaternion::Identity;		//武器の回転
	CSkinModel				m_skinmodel;									//スキンモデル
	CSkinModel				m_weaponskin[4];								//武器のスキンモデル
	CCharacterController	m_characterController;							//キャラクターコントローラー
	CLight					m_light;										//ライト
	CBoxCollider			m_weaponBoxCollider;								//武器用のボックスコライダー
	CRigidBody				m_weaponRigitBody;								//ボックス用のrigidBody

	CPad					m_pad;									//パッド
	CAnimation				m_animation;							//アニメーション
	SplayerStatus			m_status;								//プレイヤーのステータス
	bool					m_isSlip = false;						//スリップ判定
	float					m_slipSpeed = 2.0f;						//回避移動時のスピード
	EnPlayerAnimeState		m_State = enPlayerStand;				//アニメーションを遷移させるための変数
	EnPlayerWeapon			m_weaponState = EnPlayerWeapon::enSword;

	const float				RUN_SPEED	= 1.4f;				
	const float				WALK_SPEED	= 300.0f;
	const float				INTERVAL = 1.5;								//ダメージを受けた後の無敵時間
	bool					m_isDamege = false;
	float					m_animetionFrame = 0.0f;
	bool					m_isAttack = false;
	bool					m_isDied = false;
	bool					m_isGround = false;
	bool					m_intervalOn = false;
	float					m_intervalTime = 0.0f;

	CPlayerStateMachine			m_PlayerStateMachine;							//プレイヤーのアニメーションの遷移を行うステートマシーン
	CPlayerRotation				m_PlayerRotation;								//プレイヤーの回転を扱うクラス
	CPlayerMove					m_PlayerMove;									//プレイヤーの動きを扱うクラス
	std::list<CPlayerArrow*>	m_arrowList;									//弓矢のリスト

	bool					m_isWireMove = false;					//ワイヤー移動できるか
	CWireCollisionSolver	m_wireCollisionSolver;					//ワイヤー移動のコリジョン処理クラス
	CVector3				m_wirePosition;							//ワイヤー移動先の座標
};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}