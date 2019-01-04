#pragma once
#include "PlayerState.h"
//プレイヤーがダメージを受けたときのステート

class CPlayerDamage : public IPlayerState
{
public:
	void Init()override;

	void Update()override;
private:
	void Rotation();
private:
	CVector3	m_airDamageVec;
	bool		m_isSky = false;	//空中でダメージを受けたか
};

