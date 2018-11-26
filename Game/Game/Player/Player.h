#pragma once
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "PlayerArrow.h"
#include "Weapon/WeaponManager.h"
#include "PlayerSate/PlayerStateCommon.h"
#include "WireAction.h"
#include "PlayerGetter.h"
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

	//所持アイテムリストに追加
	//item		アイテムリストに追加するアイテム
	void AddItemList(IItem* item);

	//所持アイテムリストを取得
	std::list<IItem*> GetItemList()
	{
		return m_itemList;
	}

	//所持アイテムを使う
	//number		アイテムの番号
	void UseItem(int number);

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

	friend class CPlayerGetter;
private:

	//プレイヤーの回転をする関数
	void Rotation(const CVector3& stickDir);

	//アニメーションイベントが起きた時に呼ばれる処理。
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName);
private:
	static CPlayer*						m_player;								//プレイヤー
	CPlayerGetter						m_playerGetter;							//プレイヤーのゲッター
	CVector3							m_position;								//座標
	CQuaternion							m_rotation = CQuaternion::Identity;		//回転
	CSkinModel							m_skinmodel;							//スキンモデル
	CCharacterController				m_characterController;					//キャラクターコントローラー
	CAnimation							m_animation;							//アニメーション
	SplayerStatus						m_status;								//プレイヤーのステータス
	CWeaponManager						m_weaponManager;						//武器
	CPlayerStateMachine					m_PlayerStateMachine;					//プレイヤーのアニメーションの遷移を行うステートマシーン
	bool								m_isDamege = false;						//ダメージを受けてるかのフラグ
	//bool								m_isAttack = false;						//攻撃中かの判定
	bool								m_isDied = false;						//死んでいるかの判定
	bool								m_isStatusConversion = false;			//ステータスが変化したかを判定する
	bool								m_isInvinsible = false;					//無敵かのフラグ

	std::list<IItem*>					m_itemList;								//所持アイテムのリスト
	CWireAction							m_wireAction;							//ワイヤーの飛ぶかどうかの判定をしたりするところ
};

static CPlayer& GetPlayer()
{
	return CPlayer::GetInstance();
}