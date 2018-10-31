#pragma once
#include "PlayerState.h"
//弓を構えた時の状態

class CPlayerArrowAttack : public IPlayerState
{
public:

	//初期化
	void Init()override;

	//更新
	void Update()override;

	const bool IsCharge()
	{
		return	m_isCharge;
	}
private:
	float					m_animetionFrame = 0.0f;
	bool					m_isCharge = false;			//チャージ中かの判定

};

