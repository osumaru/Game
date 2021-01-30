#pragma once
#include"PlayerState.h"
#include "PlayerStateCommon.h"
//プレイヤーの攻撃(コンボ攻撃等も含む)のステート

class CPlayerAttack : public  IPlayerState
{
public:
	//コンストラクタ
	CPlayerAttack();

	//初期化
	void Init()override;
	
	//更新
	void Update()override;

	//移動
	void Move();

	//回転
	void Rotation();

	//線形補完
	void Lerp();

	//連続攻撃している回数を取得
	int GetAttackCount() const
	{
		return m_attackCount;
	}

private:
	int							m_maxAttackNum = 0;					//最大連続攻撃回数
	int							m_attackCount = 0;					//連続攻撃してる回数
	bool						m_isContinuationAttack = false;		//連続攻撃してるかのフラグ
	EnPlayerAnimation*			m_attackAnimation;					//攻撃のアニメーション番号
	EnPlayerAnimation*			m_combineAnimation;					//攻撃の後の合成用のアニメーション番号
	bool*						m_stanAttack;						//スタン攻撃
	int							m_maxWeaponHitNum;					//武器ごとの攻撃回数
	const CMatrix*				m_pBoneMat;							//ボーンの行列のポインタ
	CQuaternion					m_addRot;
	CVector3					m_rotationDirectionVector;
};

