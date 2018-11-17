#pragma once
#include "WeaponCommon.h"

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
	virtual void EnemyAttackPositionDecide(){}


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

protected:
	CPlayer*					m_pPlayer = nullptr;		//プレイヤーのインスタンス
	const CMatrix*				m_normalBoneMat = nullptr;	//プレイヤーのボーン行列
	const CMatrix*				m_attackBoneMat = nullptr;	//プレイヤーのボーン行列
	CVector3					m_position;					//通常時の座標
	CVector3					m_attackPosition;			//攻撃時の座標
	CQuaternion					m_rotation;					//通常時の回転
	CQuaternion					m_attackRotation;			//攻撃時の回転
	CVector3					m_attackCheckPos;			//当たり判定用の座標
	CSkinModel					m_skinModel;				//武器のスキンモデル
	SWeaponStatus				m_weaponStatus;				//装備中の武器ノステータス
	
};