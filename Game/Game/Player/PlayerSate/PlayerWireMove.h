/*
*	プレイヤーのワイヤー移動クラス
*/

#pragma once

#include "PlayerState.h"

class CPlayerWireMove : public IPlayerState
{
public:
	//コンストラクタ
	CPlayerWireMove() {}

	//デストラクタ
	~CPlayerWireMove() {}

	void Init()override;

	//更新
	void Update()override;

private:
	CVector3	m_movePosition;		//移動先の座標
	const float m_speed = 40.0f;	//移動速度
	float		m_accel = 0.0f;
	float		m_moveSpeed = 0.0f;
	bool		m_isWireThrow = true;
};