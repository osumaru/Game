#pragma once
#include "PlayerState.h"

class CPlayerAvoidance: public IPlayerState
{
public:
	void Init()override;

	void Update()override;
private:
	const CMatrix* m_pBoneMat;	//ボーンの行列のポインタ
	CVector3 m_manipVec;		//ボーンの座標からプレイヤーの座標までのベクトル
	CVector3 m_preBonePos;		//前のフレームのボーンの座標
};

