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

private:
	static const int			MAX_ATTACK_NUM = 3;					//最大連続攻撃回数
	float						m_animetionFrame = 0.0f;			
	int							m_attackCount = 0;					//連続攻撃してる回数
	bool						m_isContinuationAttack = false;		//連続攻撃してるかのフラグ
	EnPlayerAnimation			m_attackAnimation[MAX_ATTACK_NUM];	//攻撃のアニメーション番号
};

