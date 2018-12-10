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
		return { false, CVector3::Zero };
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

	EnPlayerAnimation& GetAttackAnimation()
	{
		return *m_attackAnimation;
	}

	EnPlayerAnimation& GetCombineAnimation()
	{
		return *m_combineAnimation;
	}

	bool& GetStanAttack()
	{
		return *m_stanAttack;
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

	int							MAX_ATTACK_NUM = 3;					//最大連続攻撃回数
	int							m_attackCount = 0;					//連続攻撃してる回数
	bool						m_isContinuationAttack = false;		//連続攻撃してるかのフラグ
	EnPlayerAnimation*			m_attackAnimation/*[MAX_ATTACK_NUM]*/;	//攻撃のアニメーション番号
	EnPlayerAnimation*			m_combineAnimation/*[MAX_ATTACK_NUM]*/;	//攻撃の後の合成用のアニメーション番号
	bool						m_isPreDodge = false;				//回避の先行入力用フラグ
	bool*						m_stanAttack;/*[MAX_ATTACK_NUM];*/
};