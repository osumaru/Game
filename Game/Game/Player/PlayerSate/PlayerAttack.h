#pragma once
#include"PlayerState.h"
class CPlayerAttack : public  IPlayerState
{
public:
	void Init()override;

	void Update()override;

private:
	float					m_animetionFrame = 0.0f;
	bool					m_conAtaack = false;
	bool					m_rock = false;			//連撃を終わらすための変数

};

