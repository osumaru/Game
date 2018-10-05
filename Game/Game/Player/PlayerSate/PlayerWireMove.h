/*
*	プレイヤーのワイヤー移動クラス
*/

#pragma once

#include "IPlayerState.h"

class CPlayerWireMove : public IPlayerState
{
public:
	//コンストラクタ
	CPlayerWireMove() {}

	//デストラクタ
	~CPlayerWireMove() {}

	//更新される前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

private:
	CVector3	m_movePosition;		//移動先の座標
	const float m_speed = 20.0f;	//移動速度
};