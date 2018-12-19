#pragma once
#include "WeaponCommon.h"
#include "WeaponTraceDraw.h"
#include "..\PlayerSate\PlayerStateCommon.h"
class CPlayer;
//武器の基底クラス

class IWeapon
{
public:
	//デストラクタ
	virtual ~IWeapon(){}

	//初期化関数
	void Init(CPlayer* player);

	//継承用用の初期化関数
	virtual void Init(){}

	//更新処理
	void Updater();
	
	//継承用の更新処理
	virtual void Update(){}

	//描画処理
	void Drawer();

	//継承用の描画処理
	virtual void Draw(){}

	//ポストエフェクト後の描画処理
	void AfterDrawer();

	//継承用のポストエフェクト後の描画処理
	virtual void AfterDraw(){}

	//エネミーとの当たり判定を取る関数
	void EnemyAttack();

	//当たり判定を取るための武器の座標を決めるための関数
	virtual SWeaponEnemyAttackInfo EnemyAttackPositionDecide()
	{
		return { false, CVector3::Zero};
	}

	//武器の軌跡を描画する座標や描画するかを決める関数
	virtual SWeaponTraceDrawInfo WeaponTraceDraw()
	{
		return { false, CVector3::Zero, CVector3::Zero };
	}

	//武器の軌跡を描画する
	void WeaponTraceDrawer();


	//武器のステータスを取得
	SWeaponStatus& GetWeaponStatus()
	{
		return m_weaponStatus;
	}

	//武器のステータスを設定
	void SetWeaponStatus(SWeaponStatus& weaponStatus)
	{
		m_weaponStatus = weaponStatus;
	}

	//攻撃モーションの先頭を取得
	EnPlayerAnimation* GetAttackAnimation()
	{
		return m_attackAnimation.get();
	}

	//攻撃終了モーションの先頭を取得
	EnPlayerAnimation* GetCombineAnimation()
	{
		return m_combineAnimation.get();
	}

	//スタン攻撃の先頭を取得
	bool* GetStanAttack()
	{
		return m_stanAttack.get();
	}

	//攻撃モーションの数を取得
	int GetMaxAttackNum()
	{
		return m_maxAttackNum;
	}

	//攻撃する武器を取得
	EnAttackWeapon* GetAttackWeapon()
	{
		return m_attackWeapon.get();
	}
protected:
	CPlayer*					m_pPlayer = nullptr;		//プレイヤーのインスタンス
	const CMatrix*				m_normalBoneMat = nullptr;	//プレイヤーのボーン行列
	const CMatrix*				m_attackBoneMat = nullptr;	//プレイヤーのボーン行列
	CVector3					m_position;					//通常時の座標
	CVector3					m_attackPosition;			//攻撃時の座標
	CQuaternion					m_rotation;					//通常時の回転
	CQuaternion					m_attackRotation;			//攻撃時の回転
	CSkinModel					m_skinModel;				//武器のスキンモデル
	SWeaponStatus				m_weaponStatus;				//装備中の武器ノステータス

	int							m_weaponNum = 0;					//武器の数
	int							m_maxAttackNum = 0;					//最大連続攻撃回数
	std::unique_ptr<EnPlayerAnimation[]>		m_attackAnimation;				//攻撃のアニメーション番号
	std::unique_ptr<EnPlayerAnimation[]>		m_combineAnimation;				//攻撃の後の合成用のアニメーション番号
	std::unique_ptr<bool[]>						m_stanAttack;						//スタン攻撃
	std::unique_ptr<EnAttackWeapon[]>			m_attackWeapon;						//攻撃する武器
};