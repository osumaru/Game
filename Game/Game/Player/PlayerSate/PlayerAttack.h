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

private:
	int							m_maxAttackNum = 0;					//最大連続攻撃回数
	int							m_attackCount = 0;					//連続攻撃してる回数
	bool						m_isContinuationAttack = false;		//連続攻撃してるかのフラグ
	EnPlayerAnimation*			m_attackAnimation;					//攻撃のアニメーション番号
	EnPlayerAnimation*			m_combineAnimation;					//攻撃の後の合成用のアニメーション番号
	bool						m_isPreDodge = false;				//回避の先行入力用フラグ
	bool*						m_stanAttack;						//スタン攻撃
	int							m_maxWeaponHitNum;					//武器ごとの攻撃回数
	const CMatrix*				m_pBoneMat;							//ボーンの行列のポインタ
	CVector3					m_manipVec;							//ボーンの座標からプレイヤーの座標までのベクトル
	CVector3					m_preBonePos;						//前のフレームのボーンの座標
};

