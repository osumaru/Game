#pragma once
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "PlayerArrow.h"
#include "Weapon/WeaponManager.h"
#include "PlayerSate/PlayerStateCommon.h"
#include "WireAction.h"
#include "PlayerGetter.h"
#include "WireDraw.h"
#include "../Item/ItemList.h"
#include "../Item/EquipList.h"
class Command;
class IItem;

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
	CPlayer() { SetIsActive(false); }
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
			m_player = New<CPlayer>(PRIORITY_PLAYER);
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

	void AfterDraw()override;

	void BeforeDead()override;

	//プレイヤーの座標を取得する関数
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//プレイヤーのステータスを取得
	const SplayerStatus& GetStatus() const
	{
		return m_status;
	}

	//武器を管理するクラスを取得
	CWeaponManager& GetWeaponManager()
	{
		return m_weaponManager;
	}

	//プレイヤーのスキンモデルの情報を取得
	const CSkinModel& GetSkinmodel() const
	{
		return m_skinmodel;
	}

	//プレイヤーが生きているかの判定
	bool GetIsDied() const
	{
		return m_isDied;
	}

	//ダメージを受けたかの判定
	bool GetIsDamage() const
	{
		return m_isDamege;
	}

	//キャラコンを取得
	const CCharacterController& GetCharacterController() const
	{
		return m_characterController;
	}

	//ステータスの計算処理を行う関数
	void StatusCalculation();

	/*プレイヤーの経験値量を上げる関数（セットする関数ではないです）
	引数で倒した敵の経験値量を入れる*/
	void ExpUP(const int expup)
	{
		if (expup <= 0) { return; }
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
		m_isStatusConversion = true;
	}

	//プレイヤーがお金を取得する
	//gold		お金
	void GainGold(const int gold)
	{
		m_status.Gold += gold;
	}

	/*
	プレイヤーのダメージ処理
	DamageValue	プレイヤーに与えるダメージ量
	*/
	void SetDamage(int DamageValue)
	{
		if (!m_isDamege && !m_isInvinsible)
		{
			m_status.Health -= DamageValue;
			m_isDamege = true;
		}
	}

	//買い物をした時の計算を行う
	bool BuyMoney(const int buy)
	{
		if (m_status.Gold < buy) { return false; }
		m_status.Gold -= buy;
		return true;
	}

	//ステータスが変化したかを取得
	const bool GetIsStatusConversion()
	{
		return m_isStatusConversion;
	}

	//ステータスが変化したかを設定
	void  SetIsStatusConversion(const bool iscon)
	{
		m_isStatusConversion = iscon;
	}

	//ワイヤーアクションを管理するクラスを取得
	CWireAction& GetWireAction()
	{
		return m_wireAction;
	}

	//ステートマシンを取得。
	CPlayerStateMachine& GetStateMachine()
	{
		return m_PlayerStateMachine;
	}

	//ダメージを与えたエネミーの座標を設定
	void SetDamageEnemyPos(const CVector3& position)
	{
		m_playerGetter.SetDamageEnemyPos(position);
	}

	//スタン攻撃かどうかを取得
	bool GetStanAttack()
	{
		return m_isStanAttack;
	}

	//スタン攻撃であるかを設定
	void SetStanAttack(bool isStanAttack)
	{
		m_isStanAttack = isStanAttack;
	}

	//スタンダメージ取得
	bool GetStanDamage()
	{
		return m_isStanDamage;
	}

	//スタンダメージ設定
	void SetStanDamage(int StanDamageValue)
	{
		if (!m_isStanDamage && !m_isInvinsible)
		{
			m_status.Health -= StanDamageValue;
			m_isStanDamage = true;
		}
	}

	//アクションをするかを取得
	bool GetIsAction()
	{
		return m_isAction;
	}

	//アクションをするかを設定
	//isAction		アクションをするか
	void SetIsAction(bool isAction)
	{
		m_isAction = isAction;
	}

	/*
	その状態へ遷移するための条件を満たしているかのフラグを返す関数
	state	プレイヤーのステート
	ret		状態
	*/
	bool GetIsStateCondition(CPlayerState::EnPlayerState state);

	//腰のボーンの番号を取得
	int GetSpineBoneID() const
	{
		return m_spineBoneID;
	}

	static CItemList& GetItemList()
	{
		return m_itemList;
	}

	static CEquipList& GetEquipList()
	{
		return m_equipList;
	}

	//即時コマンドの設定
	void SetCommand(Command* command)
	{
		if (m_command != nullptr)
		{
			delete m_command;
		}
		m_command = command;
	}

	//遅延コマンドの設定
	void SetDefferdCommand(Command* command)
	{

		if (m_defferdCommand != nullptr)
		{
			delete m_defferdCommand;
		}
		m_defferdCommand = command;
	}

	void ResetCommand()
	{
		if (m_command != nullptr)
		{
			delete m_command;
			m_command = nullptr;
		}
		if (m_defferdCommand != nullptr)
		{
			delete m_defferdCommand;
			m_defferdCommand = nullptr;
		}
	}
	friend class CPlayerGetter;
private:

	//プレイヤーの回転をする関数
	void Rotation(const CVector3& stickDir);

	//アニメーションイベントが起きた時に呼ばれる処理。
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);
private:
	Command*							m_command = nullptr;					//即時コマンド
	Command*							m_defferdCommand = nullptr;				//遅延コマンド
	static CEquipList					m_equipList;
	static CItemList					m_itemList;								//アイテムリスト
	static CPlayer*						m_player;								//プレイヤー
	CPlayerGetter						m_playerGetter;							//プレイヤーのゲッター
	CVector3							m_position;								//座標
	CQuaternion							m_rotation = CQuaternion::Identity;		//回転
	CSkinModel							m_skinmodel;							//スキンモデル
	CCharacterController				m_characterController;					//キャラクターコントローラー
	CAnimation							m_animation;							//アニメーション
	static SplayerStatus				m_status;								//プレイヤーのステータス
	CWeaponManager						m_weaponManager;						//武器
	CPlayerStateMachine					m_PlayerStateMachine;					//プレイヤーのアニメーションの遷移を行うステートマシーン
	bool								m_isDamege = false;						//ダメージを受けてるかのフラグ
	//bool								m_isAttack = false;						//攻撃中かの判定
	bool								m_isDied = false;						//死んでいるかの判定
	bool								m_isStatusConversion = false;			//ステータスが変化したかを判定する
	bool								m_isInvinsible = false;					//無敵かのフラグ
	CWireAction							m_wireAction;							//ワイヤーの飛ぶかどうかの判定をしたりするところ
	CWireDraw							m_wireDraw;								//ワイヤーを描画する
	bool								m_isStanAttack = false;					//スタン攻撃
	bool								m_isStanDamage = false;					//スタンダメージ
	CCollisionDetection					m_groundCollision;						//地面用のコリジョン
	CBoxCollider						m_boxCollider;							//ボックスコライダー
	bool								m_isAction = true;						//アクションをするかを判定する
	const CMatrix*						m_hipBoneMat;							//腰のボーン行列のポインタ
	CLight								m_light;
	int									m_spineBoneID;							//腰の骨のID
};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}

static CItemList& GetItemList()
{
	return CPlayer::GetItemList();
}

static CEquipList& GetEquipList()
{
	return CPlayer::GetEquipList();
}