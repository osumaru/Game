#pragma once
#include"PlayerState.h"

class CPlayerRun	: public	IPlayerState
{
public:
	void Init()override;

	void Update()override;
private:
	float	m_accel = 0.0f;
	float	m_moveSpeed = 0.0f;
	float	m_timer = 0.0f;		//タイマー
	bool	m_isDash = false;	//ダッシュしているか
};

