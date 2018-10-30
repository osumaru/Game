#pragma once
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "PlayerArrow.h"
#include "Weapon.h"
#include "PlayerSate/PlayerStateCommon.h"

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

	//プレイヤーの初期化
	void Init(CVector3 position);

	//プレイヤーのインスタンスの取得
	static CPlayer& GetInstance()
	{
		return *m_player;
	}

	//インスタンスの生成
	static void CPlayer::Create()
	{
		if (!m_player)
		{
			m_player = New<CPlayer>(1);
		}
	}

	//インスタンスの消去
	static void CPlayer::Destroy()
	{
		Delete(m_player);
		m_player = nullptr;
	}

	//プレイヤーの更新関数
	void Update()override;

	//プレイヤーの描画関数
	void Draw()override;

	//プレイヤーの座標を取得する関数
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	//プレイヤーの座標を設定する関数
	void SetPosition(const CVector3 setpos)
	{
		 m_characterController.SetPosition(setpos);
	}
	//プレイヤーの回転情報を取得
	const CQuaternion& GetPlayerrRot()
	{
		return m_rotation;
	}

	//アニメーションの情報を取得
	const CAnimation& GetAnimation() const
	{
		return m_animation;
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
	void SetPlayerAnimation(EnPlayerAnimation animNumber, const float num)
	{
		m_animation.Play(animNumber, num);
		m_State = animNumber;
	}

	//プレイヤーのステータスを取得
	const SplayerStatus& GetStatus() const
	{
		return m_status;
	}

	//プレイヤーのワールド行列を取得
	const CMatrix& GetWorldMatrix() const
	{
		return m_skinmodel.GetWorldMatrix();
	}

	//プレイヤーのスピードを取得する
	const CVector3& GetMoveSpeed() const
	{
		return m_characterController.GetMoveSpeed();
	}

	//プレイヤーの頭のボーンの位置を取得
	CVector3 GetPlayerHead() const
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
	bool GetIsDied() const
	{
		return m_isDied;
	}

	//死亡したかを設定
	void SetIsDeid(bool SetDied)
	{
		m_isDied = SetDied;
	}

	//ダメージを受けたかの判定
	bool GetIsDamage() const
	{
		return m_isDamege;
	}

	//ダメージを受けたかの設定
	void SetIsDamage(bool SetDamage)
	{
		m_isDamege = SetDamage;
	}
	//攻撃中かを取得
	bool GetIsAttack() const
	{
		return m_isAttack;
	}

	//攻撃をしたかの設定
	void SetAttack(bool SetA)
	{
		m_isAttack = SetA;
	}

	//ステートマシーンのしゅとく
	CPlayerStateMachine& GetPlayerStateMachine()
	{
		return m_PlayerStateMachine;
	}

	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

	const CWeapon& GetWeapon() const
	{
		return m_weapon;
	}
	
	//プレイヤーのスキンモデルの情報を取得
	const CSkinModel& GetPlayerSkin() const
	{
		return m_skinmodel;
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

	const CCharacterController& GetCharacterController() const
	{
		return m_characterController;
	}

	//ワイヤー移動しているか
	bool IsWireMove()
	{
		return m_isWireMove;
	}
	

	//ワイヤー移動しているかを設定
	void SetIsWireMove(bool isWireMove)
	{
		m_isWireMove = isWireMove;
	}

	//矢を生成しているかの設定
	void SetInitArrow(const bool set)
	{
		m_initArrow = set;
	}


	void SetAnimationPlay(EnPlayerAnimation state, float interporationTime)
	{
		m_animation.Play(state, interporationTime);
	}

	void SetAnimationPlay(EnPlayerAnimation state)
	{
		m_animation.Play(state);
	}

	//弓を生成する関数
	void InitArrow();
private:
	void PlayerMove();

	void Rotation();

	//アニメーションイベントが起きた時に呼ばれる処理。
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);
private:
	static CPlayer*				m_player;								//プレイヤー
	CWeapon					m_weapon;
	CVector3				m_position;									//座標
	CQuaternion				m_rotation = CQuaternion::Identity;			//回転
	CSkinModel				m_skinmodel;								//スキンモデル
	CCharacterController	m_characterController;						//キャラクターコントローラー
	CAnimation				m_animation;								//アニメーション
	SplayerStatus			m_status;									//プレイヤーのステータス
	bool					m_isSlip = false;							//スリップ判定
	float					m_slipSpeed = 2.0f;							//回避移動時のスピード
	EnPlayerAnimation		m_State = enPlayerAnimationStand;			//アニメーションを遷移させるための変数
	const float				INTERVAL = 1.5;								//ダメージを受けた後の無敵時間
	bool					m_isDamege = false;
	float					m_animetionFrame = 0.0f;
	bool					m_isAttack = false;							//攻撃中かの判定
	bool					m_isDied = false;							//死んでいるかの判定
	bool					m_intervalOn = false;						//無敵中かの判定
	bool					m_initArrow = false;						//弓を生成しているかの判定
	float					m_intervalTime = 0.0f;

	CPlayerStateMachine			m_PlayerStateMachine;							//プレイヤーのアニメーションの遷移を行うステートマシーン
	std::list<CPlayerArrow*>	m_arrowList;									//弓矢のリスト
	CSprite						m_arrowtag;										//サークルのスプライト
	CTexture					m_arrowtexture;
	bool						m_isZoom;										//弓用の視点に切り替えるかの判定をする変数

	bool					m_isWireMove = false;					//ワイヤー移動できるか
	CRayTest				m_wireCollisionSolver;					//ワイヤー移動のコリジョン処理クラス
	CVector3				m_wirePosition;							//ワイヤー移動先の座標
};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}