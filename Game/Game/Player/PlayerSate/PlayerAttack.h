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

	void Move();

private:
	static const int			MAX_ATTACK_NUM = 3;					//最大連続攻撃回数
	int							m_attackCount = 0;					//連続攻撃してる回数
	bool						m_isContinuationAttack = false;		//連続攻撃してるかのフラグ
	EnPlayerAnimation			m_attackAnimation[MAX_ATTACK_NUM];	//攻撃のアニメーション番号
	EnPlayerAnimation			m_combineAnimation[MAX_ATTACK_NUM];	//攻撃の後の合成用のアニメーション番号
	bool						m_isPreDodge = false;				//回避の先行入力用フラグ

	const CMatrix* m_pBoneMat;	//ボーンの行列のポインタ
	CVector3 m_manipVec;		//ボーンの座標からプレイヤーの座標までのベクトル
	CVector3 m_preBonePos;		//前のフレームのボーンの座標
};

